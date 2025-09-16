// WICHelper.cpp
#include "WICHelper.h"
#pragma link "windowscodecs.lib"
#pragma link "ole32.lib"

TWICHelper::TWICHelper() : FFactory(nullptr), FInitialized(false) {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (SUCCEEDED(hr)) {
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_IWICImagingFactory,
            (LPVOID*)&FFactory
        );
        FInitialized = SUCCEEDED(hr);
    }
}

TWICHelper::~TWICHelper() {
    if (FFactory) {
        FFactory->Release();
        FFactory = nullptr;
    }
    CoUninitialize();
}

String TWICHelper::GetErrorMessage(HRESULT hr) {
    switch (hr) {
        case WINCODEC_ERR_COMPONENTNOTFOUND:
            return L"Codec not found";
        case WINCODEC_ERR_INSUFFICIENTBUFFER:
            return L"Insufficient buffer";
        case WINCODEC_ERR_INVALIDPARAMETER:
            return L"Invalid parameter";
        case WINCODEC_ERR_NOTINITIALIZED:
            return L"Not initialized";
        case WINCODEC_ERR_UNSUPPORTEDOPERATION:
            return L"Unsupported operation";
        case WINCODEC_ERR_UNSUPPORTEDPIXELFORMAT:
            return L"Unsupported pixel format";
        case WINCODEC_ERR_WRONGSTATE:
            return L"Wrong state";
        default:
            return String().sprintf(L"WIC Error: 0x%08X", hr);
    }
}

bool TWICHelper::LoadImage(const String& fileName, TBitmap* bitmap) {
    if (!FInitialized || !bitmap) return false;

    IWICBitmapDecoder* pDecoder = nullptr;
    IWICBitmapFrameDecode* pFrame = nullptr;

    try {
        // Create decoder
        HRESULT hr = FFactory->CreateDecoderFromFilename(
            fileName.c_str(),
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &pDecoder
        );

        if (FAILED(hr)) {
            throw Exception(GetErrorMessage(hr));
        }

        // Get first frame
        hr = pDecoder->GetFrame(0, &pFrame);
        if (FAILED(hr)) {
            throw Exception(GetErrorMessage(hr));
        }

        // Convert to bitmap
        bool result = ConvertFrameToBitmap(pFrame, bitmap);

        pFrame->Release();
        pDecoder->Release();

        return result;

    } catch (...) {
        if (pFrame) pFrame->Release();
        if (pDecoder) pDecoder->Release();
        return false;
    }
}

TBitmap* TWICHelper::LoadImage(const String& fileName) {
	if (!FInitialized) return NULL;

    TBitmap* bitmap = new TBitmap();
    IWICBitmapDecoder* pDecoder = nullptr;
    IWICBitmapFrameDecode* pFrame = nullptr;

    try {
        // Create decoder
        HRESULT hr = FFactory->CreateDecoderFromFilename(
            fileName.c_str(),
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &pDecoder
        );

        if (FAILED(hr)) {
            throw Exception(GetErrorMessage(hr));
        }

        // Get first frame
        hr = pDecoder->GetFrame(0, &pFrame);
        if (FAILED(hr)) {
            throw Exception(GetErrorMessage(hr));
        }

        // Convert to bitmap
        bool result = ConvertFrameToBitmap(pFrame, bitmap);

        pFrame->Release();
        pDecoder->Release();

		return bitmap;
    } catch (...) {
        if (pFrame) pFrame->Release();
        if (pDecoder) pDecoder->Release();
        return NULL;
    }
}

bool TWICHelper::LoadImageFromStream(TStream* stream, TBitmap* bitmap) {
	if (!FInitialized || !stream || !bitmap) return false;

	IWICStream* pStream = nullptr;
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;

	try {
		// Create WIC stream
        HRESULT hr = FFactory->CreateStream(&pStream);
        if (FAILED(hr)) return false;

        // Load stream data into memory
        stream->Position = 0;
        int size = stream->Size;
        std::unique_ptr<BYTE[]> buffer(new BYTE[size]);
        stream->ReadBuffer(buffer.get(), size);

        // Initialize WIC stream
        hr = pStream->InitializeFromMemory(buffer.get(), size);
        if (FAILED(hr)) {
            pStream->Release();
            return false;
        }

        // Create decoder
        hr = FFactory->CreateDecoderFromStream(
            pStream,
            nullptr,
            WICDecodeMetadataCacheOnLoad,
            &pDecoder
        );

        if (FAILED(hr)) {
            pStream->Release();
            return false;
        }

        // Get frame
        hr = pDecoder->GetFrame(0, &pFrame);
        if (FAILED(hr)) {
            pDecoder->Release();
            pStream->Release();
            return false;
        }

        bool result = ConvertFrameToBitmap(pFrame, bitmap);

        pFrame->Release();
        pDecoder->Release();
        pStream->Release();

        return result;
    } catch (...) {
        if (pFrame) pFrame->Release();
        if (pDecoder) pDecoder->Release();
        if (pStream) pStream->Release();
        return false;
    }
}

bool TWICHelper::ConvertFrameToBitmap(IWICBitmapFrameDecode* pFrame, TBitmap* bitmap) {
    if (!pFrame || !bitmap) return false;

    IWICFormatConverter* pConverter = nullptr;

    try {
        UINT width, height;
        HRESULT hr = pFrame->GetSize(&width, &height);
        if (FAILED(hr)) return false;

        // Create format converter
        hr = FFactory->CreateFormatConverter(&pConverter);
        if (FAILED(hr)) return false;

        // Convert to 32bpp BGRA
        hr = pConverter->Initialize(
            pFrame,
            GUID_WICPixelFormat32bppBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            0.0,
            WICBitmapPaletteTypeCustom
        );

        if (FAILED(hr)) {
            pConverter->Release();
            return false;
        }

        // Set bitmap size
        bitmap->PixelFormat = pf32bit;
        bitmap->Width = width;
        bitmap->Height = height;

        // Copy pixel data
        UINT stride = width * 4; // 32bpp = 4 bytes per pixel
        UINT bufferSize = stride * height;

        for (int y = 0; y < (int)height; y++) {
            BYTE* scanLine = (BYTE*)bitmap->ScanLine[y];
            WICRect rect = {0, y, (INT)width, 1};
            hr = pConverter->CopyPixels(
                &rect,
                stride,
                stride,
                scanLine
            );
            if (FAILED(hr)) {
                pConverter->Release();
                return false;
            }
        }

        // Alternative methods (commented out):
        // WICRect rect = {0, y, (INT)width, 1};
        // pConverter->CopyPixels(&rect, stride, stride, scanLine);

        // Copy entire image at once:
        // pConverter->CopyPixels(nullptr, stride, stride, scanLine);

        // More efficient method:
        // UINT totalSize = stride * height;
        // std::vector<BYTE> buffer(totalSize);
        // hr = pConverter->CopyPixels(nullptr, stride, totalSize, buffer.data());
        // if (SUCCEEDED(hr)) {
        //     // Copy from buffer to bitmap
        //     for (int y = 0; y < (int)height; y++) {
        //         BYTE* scanLine = (BYTE*)bitmap->ScanLine[y];
        //         memcpy(scanLine, buffer.data() + (y * stride), stride);
        //     }
        // }

        pConverter->Release();
        return true;

    } catch (...) {
        if (pConverter) pConverter->Release();
        return false;
    }
}

bool TWICHelper::SaveImage(TBitmap* bitmap, const String& fileName, int quality) {
    if (!FInitialized || !bitmap) return false;

    // Determine format from file extension
    String ext = ExtractFileExt(fileName).LowerCase();
    GUID containerFormat;

    if (ext == L".jpg" || ext == L".jpeg") {
        containerFormat = GUID_ContainerFormatJpeg;
    } else if (ext == L".png") {
        containerFormat = GUID_ContainerFormatPng;
    } else if (ext == L".bmp") {
        containerFormat = GUID_ContainerFormatBmp;
    } else if (ext == L".tiff" || ext == L".tif") {
        containerFormat = GUID_ContainerFormatTiff;
    } else {
        return false; // Unsupported format
    }

    IWICBitmapEncoder* pEncoder = CreateEncoder(fileName, containerFormat);
    if (!pEncoder) return false;

    IWICBitmapFrameEncode* pFrameEncode = nullptr;
    IPropertyBag2* pPropertyBag = nullptr;

    try {
        // Create frame
        HRESULT hr = pEncoder->CreateNewFrame(&pFrameEncode, &pPropertyBag);
        if (FAILED(hr)) {
            pEncoder->Release();
            return false;
        }

        // Set JPEG quality
        if (containerFormat == GUID_ContainerFormatJpeg && pPropertyBag) {
            PROPBAG2 option = {0};
            option.pstrName = L"ImageQuality";
            VARIANT varValue;
            VariantInit(&varValue);
            varValue.vt = VT_R4;
            varValue.fltVal = quality / 100.0f;
            pPropertyBag->Write(1, &option, &varValue);
            VariantClear(&varValue);
        }

        // Initialize frame
        hr = pFrameEncode->Initialize(pPropertyBag);
        if (FAILED(hr)) {
            if (pPropertyBag) pPropertyBag->Release();
            pFrameEncode->Release();
            pEncoder->Release();
            return false;
        }

        // Set size and pixel format
        UINT width = bitmap->Width;
        UINT height = bitmap->Height;
        WICPixelFormatGUID pixelFormat = GUID_WICPixelFormat32bppBGRA;

        pFrameEncode->SetSize(width, height);
        pFrameEncode->SetPixelFormat(&pixelFormat);

        // Write pixel data
        UINT stride = width * 4;
        for (int y = 0; y < (int)height; y++) {
            BYTE* scanLine = (BYTE*)bitmap->ScanLine[y];
            hr = pFrameEncode->WritePixels(1, stride, stride, scanLine);
            if (FAILED(hr)) break;
        }

        if (SUCCEEDED(hr)) {
            hr = pFrameEncode->Commit();
            if (SUCCEEDED(hr)) {
                hr = pEncoder->Commit();
            }
        }

        if (pPropertyBag) pPropertyBag->Release();
        pFrameEncode->Release();
        pEncoder->Release();

        return SUCCEEDED(hr);

    } catch (...) {
        if (pPropertyBag) pPropertyBag->Release();
        if (pFrameEncode) pFrameEncode->Release();
        pEncoder->Release();
        return false;
    }
}

IWICBitmapEncoder* TWICHelper::CreateEncoder(const String& fileName, GUID& containerFormat) {
    IWICBitmapEncoder* pEncoder = nullptr;
    IWICStream* pStream = nullptr;

    try {
        // Create stream
        HRESULT hr = FFactory->CreateStream(&pStream);
        if (FAILED(hr)) return nullptr;

        // Initialize from filename
        hr = pStream->InitializeFromFilename(fileName.c_str(), GENERIC_WRITE);
        if (FAILED(hr)) {
            pStream->Release();
            return nullptr;
        }

        // Create encoder
        hr = FFactory->CreateEncoder(containerFormat, nullptr, &pEncoder);
        if (FAILED(hr)) {
            pStream->Release();
            return nullptr;
        }

        // Initialize encoder
        hr = pEncoder->Initialize(pStream, WICBitmapEncoderNoCache);
        if (FAILED(hr)) {
            pEncoder->Release();
            pStream->Release();
            return nullptr;
        }

        pStream->Release(); // Encoder manages the stream
        return pEncoder;

    } catch (...) {
        if (pStream) pStream->Release();
        if (pEncoder) pEncoder->Release();
        return nullptr;
    }
}

bool TWICHelper::GetImageInfo(const String& fileName, UINT& width, UINT& height,
                             WICPixelFormatGUID& pixelFormat) {
    if (!FInitialized) return false;

    IWICBitmapDecoder* pDecoder = nullptr;
    IWICBitmapFrameDecode* pFrame = nullptr;

    try {
        HRESULT hr = FFactory->CreateDecoderFromFilename(
            fileName.c_str(),
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &pDecoder
        );

        if (FAILED(hr)) return false;

        hr = pDecoder->GetFrame(0, &pFrame);
        if (FAILED(hr)) {
            pDecoder->Release();
            return false;
        }

        hr = pFrame->GetSize(&width, &height);
        if (SUCCEEDED(hr)) {
            hr = pFrame->GetPixelFormat(&pixelFormat);
        }

        pFrame->Release();
        pDecoder->Release();

        return SUCCEEDED(hr);

    } catch (...) {
        if (pFrame) pFrame->Release();
        if (pDecoder) pDecoder->Release();
        return false;
    }
}

bool TWICHelper::IsSupportedFormat(const String& fileName) {
    String ext = ExtractFileExt(fileName).LowerCase();
    return (ext == L".jpg" || ext == L".jpeg" || ext == L".png" ||
            ext == L".bmp" || ext == L".tiff" || ext == L".tif" ||
            ext == L".gif" || ext == L".ico");
}

bool TWICHelper::ResizeImage(const String& srcFileName, const String& dstFileName,
                            UINT newWidth, UINT newHeight, int quality) {
    if (!FInitialized) return false;

    TBitmap* tempBitmap = new TBitmap();
    try {
        // Load source image
        if (!LoadImage(srcFileName, tempBitmap)) {
            delete tempBitmap;
            return false;
        }

        // Resize
        TBitmap* resizedBitmap = new TBitmap();
        try {
            resizedBitmap->PixelFormat = tempBitmap->PixelFormat;
            resizedBitmap->Width = newWidth;
            resizedBitmap->Height = newHeight;

            // High quality resize
            TRect srcRect(0, 0, tempBitmap->Width, tempBitmap->Height);
            TRect dstRect(0, 0, newWidth, newHeight);

            resizedBitmap->Canvas->StretchDraw(dstRect, tempBitmap);

            // Save
            bool result = SaveImage(resizedBitmap, dstFileName, quality);
            delete resizedBitmap;
            delete tempBitmap;
            return result;

        } catch (...) {
            delete resizedBitmap;
            delete tempBitmap;
            return false;
        }

    } catch (...) {
        delete tempBitmap;
        return false;
    }
}

bool TWICHelper::ConvertFormat(const String& srcFileName, const String& dstFileName,
                              int quality) {
    if (!FInitialized) return false;

    TBitmap* bitmap = new TBitmap();
    try {
        if (!LoadImage(srcFileName, bitmap)) {
            delete bitmap;
            return false;
        }

        bool result = SaveImage(bitmap, dstFileName, quality);
        delete bitmap;
        return result;

    } catch (...) {
        delete bitmap;
        return false;
    }
}


