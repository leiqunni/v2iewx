//=============================================================================
// Susie Plug-in Header
//                                from Susie 32bit Plug-in rev4.1 (c) たけちん
//                     Corded by GOK @ Assemblage Laboratry. (gok@grace.ne.jp)
//=============================================================================

#ifndef _INC_SPI_PLUGIN_H_
#define _INC_SPI_PLUGIN_H_

#include "time.h"  // SPI_ARCHIVEINFO構造体用

#ifdef __cplusplus  // "C"宣言
extern "C" {
#endif

//-----------------------------------------------------------------------------
// 構造体
//-----------------------------------------------------------------------------
#include "pshpack1.h"  // エイリアスを1バイトにする

typedef struct {
	long left;       // 画像を展開する位置(left)
	long top;        // 画像を展開する位置(top)
	long width;      // 画像の幅  (pixel)
	long height;     // 画像の高さ(pixel)
	WORD x_density;  // 画素の水平方向密度
	WORD y_density;  // 画素の垂直方高密度
	short bpp;       // １画素辺りのbit数
	HLOCAL info;     // 画像内のテキスト情報(LocalAlloc値)
} SPI_PICTUREINFO, *LPSPI_PICTUREINFO;

typedef struct {
	unsigned char method[8];  // 圧縮法の種類
	unsigned long pos;        // ファイル上での位置
	unsigned long compsize;   // 圧縮されたサイズ
	unsigned long filesize;   // 元のファイルサイズ
	time_t timestamp;         // ファイルの更新日時
	char path[200];           // 相対パス
	char filename[200];       // ファイル名
	unsigned long crc;        // CRC
} SPI_ARCHIVEINFO, *LPSPI_ARCHIVEINFO;

#include "poppack.h"  // エイリアス宣言を閉じる

//-----------------------------------------------------------------------------
// エラーコード
//-----------------------------------------------------------------------------
#define SPI_ERR_SUCCESS 0        // 正常終了
#define SPI_ERR_NOTIMPRIMENT -1  // その機能はインプリメントされていない
#define SPI_ERR_STOPCALLBACK 1   // コールバックが、非0を返した
#define SPI_ERR_UNKOWNFORMAT 2   // 未知のフォーマット
#define SPI_ERR_BROKEDATA 3      // データが壊れている
#define SPI_ERR_NOMEMORYALLOC 4  // メモリが確保できない
#define SPI_ERR_MEMORYERROR 5    // メモリエラー(Lock等)
#define SPI_ERR_NOFILEREAD 6     // ファイルリードエラー
#define SPI_ERR_RESERVED 7       // (予約)
#define SPI_ERR_INNERERROR 8     // 内部エラー

//-----------------------------------------------------------------------------
// その他の定数など
//-----------------------------------------------------------------------------
#define SPI_PICINFOFLAG(f) (f & 0x07)
#define SPI_PICINFODEST(f) ((f >> 8) & 0x07)
#define SPI_PICINFOSRC(f) (f & 0x07)

typedef int(CALLBACK* LPSPI_CALLBACK)(int num, int max, long ldata);

//-----------------------------------------------------------------------------
// [共通関数] Plug-inに関する情報を得る
//-----------------------------------------------------------------------------
int __declspec(dllexport) WINAPI GetPluginInfo(int n,          // 取得する情報番号
                                               LPSTR buf,      // 情報を格納する領域
                                               int buf_size);  // 領域のサイズ

// 返値     書き込んだバッファ数
//          情報番号が無効なときは、0を返す

// int n の内容
//    0    : Plug-inのAPIバージョン     "00IN" : Import  - Normal
//                                      "00AM" : Archive - Multi Picture
//    1    : Plug-in名,バージョン,コピーライト等
//    2n+2 : 代表的な拡張子("*.jpg" "*.rgb;*.q0" 等)
//    2n+3 : ファイル形式名(openダイアログに表示される内容)

//-----------------------------------------------------------------------------
// [00IN関数] 展開可能なファイル形式か調べる
//-----------------------------------------------------------------------------
int __declspec(dllexport) WINAPI IsSupported(LPSTR filename,  // ファイル名
                                             DWORD dw);       // 上位ワードが 0のとき、ファイルハンドル
                                                              // 上位ワードが 非0のとき、ファイル先頭部(2KB
                                                              // 以上)を読み込んだバッファへのポインタ

// 返値     0   対応しないフォーマット
//          非0 対応しているフォーマット

// filenameにはフルパスのポインタが渡される。
// 通常はdwでチェックを行い、filenameは特殊なケース(拡張子で判断する)でのみ使用する。

//-----------------------------------------------------------------------------
// [00IN関数] 画像ファイルに関する情報を得る
//-----------------------------------------------------------------------------
int __declspec(dllexport) WINAPI GetPictureInfo(LPSTR buf,                // flagがファイルの場合、ファイル名
                                                                          // flagがメモリの場合、ファイルイメージポインタ
                                                long len,                 // flagがファイルの場合、読み込み開始オフセット
                                                                          // flagがメモリの場合、データサイズ
                                                unsigned int flag,        // SPI_PICINFOFLAG(flag) : 0 (ディスクファイル)
                                                                          //                       : 1 (メモリイメージ)
                                                LPSPI_PICTUREINFO info);  // 構造体に格納するポインタ

// 返値     エラーコード。正常終了は 0を返す。

//-----------------------------------------------------------------------------
// [00IN関数] 画像を展開する
//-----------------------------------------------------------------------------
int __declspec(dllexport) WINAPI GetPicture(LPSTR buf,                // flagがファイルの場合、ファイル名
                                                                      // flagがメモリの場合、ファイルイメージポインタ
                                            long len,                 // flagがファイルの場合、読み込み開始オフセット
                                                                      // flagがメモリの場合、データサイズ
                                            unsigned int flag,        // SPI_PICINFOFLAG(flag) : 0 (ディスクファイル)
                                                                      //                       : 1 (メモリイメージ)
                                            HLOCAL* info,             // BITMAPINFOのあるメモリハンドルのポインタ
                                            HLOCAL* bm,               // BITMAP本体のメモリハンドルのポインタ
                                            LPSPI_CALLBACK callback,  // コールバック関数のポインタ
                                            long ldata);              // コールバック関数のパラメータ

// 返値     エラーコード。正常終了は 0を返す。

// *info,*bmは、アプリケーション側でLocalFreeしてメモリを開放する必要がある。
// コールバック関数は、まずnum=0で呼び、num=maxまで定期的に呼び続ける。
// コールバック関数の戻り値が非0のときは処理を中断する。

//-----------------------------------------------------------------------------
// [00IN関数] プレビュー・カタログ表示用画像縮小展開
//-----------------------------------------------------------------------------
int __declspec(dllexport) WINAPI GetPreview(LPSTR buf,          // flagがファイルの場合、ファイル名
                                                                // flagがメモリの場合、ファイルイメージポインタ
                                            long len,           // flagがファイルの場合、読み込み開始オフセット
                                                                // flagがメモリの場合、データサイズ
                                            unsigned int flag,  // SPI_PICINFOFLAG(flag) : 0 (ディスクファイル)
                                                                //                       : 1 (メモリイメージ)
                                            HLOCAL* info,       // BITMAPINFOのあるメモリハンドルのポインタ
                                            HLOCAL* bm,         // BITMAP本体のメモリハンドルのポインタ
                                            FARPROC callback,   // コールバック関数のポインタ
                                            long ldata);        // コールバック関数のパラメータ

// 返値     エラーコード。正常終了は 0を返す。
//          この関数はオプションで、未対応の場合は SPI_ERR_NOTIMPRIMENT(-1)を返す。

//-----------------------------------------------------------------------------
// [00IN関数] Plug-in設定ダイアログの表示
//-----------------------------------------------------------------------------
int __declspec(dllexport) WINAPI ConfigurationDlg(HWND parent,  // 親ウィンドウのウィンドウハンドル
                                                  int fnc);     // 機能コード
                                                                //   0      Plug-inのaboutダイアログ表示
                                                                //   1      設定ダイアログ表示
                                                                //   2以上  予約

// 返値     エラーコード。正常終了は 0を返す。
//          この関数はオプションで、未対応の場合には-1を返すか実装しない。

//-----------------------------------------------------------------------------
// [00AM関数] 展開可能なファイル形式か調べる
//-----------------------------------------------------------------------------
// int __declspec(dllexport) WINAPI IsSupported(
//	LPSTR filename,				// ファイル名
//	DWORD dw);					// 上位ワードが 0のとき、ファイルハンドル
//								// 上位ワードが 非0のとき、ファイル先頭部(2KB
//								// 以上)を読み込んだバッファへのポインタ

// 返値     0   対応しないフォーマット
//          非0 対応しているフォーマット

//-----------------------------------------------------------------------------
// [00AM関数] アーカイブ内の全てのファイルの情報を取得する
//-----------------------------------------------------------------------------
int __declspec(dllexport) WINAPI GetArchiveInfo(LPSTR buf,          // flagがファイルの場合、ファイル名
                                                                    // flagがメモリの場合、ファイルイメージポインタ
                                                long len,           // flagがファイルの場合、読み込み開始オフセット
                                                                    // flagがメモリの場合、データサイズ
                                                unsigned int flag,  // SPI_PICINFOFLAG(flag) : 0 (ディスクファイル)
                                                                    //                       : 1 (メモリイメージ)
                                                HLOCAL* info);      // ファイル情報の入ったハンドルのポインタ
                                                                    // SPI_ARCHIVEINFO.method[0] == '\0'で終端

// 返値     エラーコード。正常終了は 0を返す。

//-----------------------------------------------------------------------------
// [00AM関数] アーカイブ内の指定したファイルの情報を取得する
//-----------------------------------------------------------------------------
int __declspec(dllexport) WINAPI GetFileInfo(LPSTR buf,                // flagがファイルの場合、ファイル名
                                                                       // flagがメモリの場合、ファイルイメージポインタ
                                             long len,                 // flagがファイルの場合、読み込み開始オフセット
                                                                       // flagがメモリの場合、データサイズ
                                             LPSTR filename,           // 情報を取得するファイル名
                                                                       // (アーカイブ内の相対パスも含める)
                                             unsigned int flag,        // SPI_PICINFOFLAG(flag) : 0 (ディスクファイル)
                                                                       //                       : 1 (メモリイメージ)
                                             LPSPI_ARCHIVEINFO info);  // 情報を受け取る構造体のポインタ

// 返値     エラーコード。正常終了は 0を返す。

//-----------------------------------------------------------------------------
// [00AM関数] アーカイブ内のファイルを取得する
//-----------------------------------------------------------------------------
int __declspec(dllexport) WINAPI GetFile(LPSTR src,                // flagがファイルの場合、ファイル名
                                                                   // flagがメモリの場合、ファイルイメージポインタ
                                         long len,                 // flagがファイルの場合、読み込み開始オフセット
                                                                   // flagがメモリの場合、データサイズ
                                         LPSTR dest,               // flagがファイルの場合、出力先ディレクトリ
                                                                   // flagがメモリの場合、出力先HLOCALのポインタ
                                         unsigned int flag,        // SPI_PICINFODEST(flag) : 0 (ディスクファイル)
                                                                   //                       : 1 (メモリイメージ)
                                                                   // SPI_PICINFOSRC(flag)  : 0 (ディスクファイル)
                                                                   //                       : 1 (メモリイメージ)
                                         LPSPI_CALLBACK callback,  // コールバック関数のポインタ
                                         long ldata);              // コールバック関数のパラメータ

// 返値     エラーコード。正常終了は 0を返す。

// コールバック関数は、まずnum=0で呼び、num=maxまで定期的に呼び続ける。
// コールバック関数の戻り値が非0のときは処理を中断する。

//-----------------------------------------------------------------------------
// [00AM関数] Plug-in設定ダイアログの表示
//-----------------------------------------------------------------------------
// int __declspec(dllexport) WINAPI ConfigurationDlg(
//	HWND parent,				// 親ウィンドウのウィンドウハンドル
//	int fnc);					// 機能コード
//								//   0      Plug-inのaboutダイアログ表示
//								//   1      設定ダイアログ表示
//								//   2以上  予約

// 返値     エラーコード。正常終了は 0を返す。
//          この関数はオプションで、未対応の場合には-1を返すか実装しない。

//-----------------------------------------------------------------------------
// プラグイン呼び出し用
//-----------------------------------------------------------------------------
typedef int(WINAPI* SPI_GETPLUGININFO)(int, LPSTR, int);
typedef int(WINAPI* SPI_ISSUPPORTED)(LPSTR, DWORD);
typedef int(WINAPI* SPI_GETPICTUREINFO)(LPSTR, long, unsigned int, LPSPI_PICTUREINFO);
typedef int(WINAPI* SPI_GETPICTURE)(LPSTR, long, unsigned int, HLOCAL*, HLOCAL*, LPSPI_CALLBACK, long);
typedef int(WINAPI* SPI_GETPREVIEW)(LPSTR, long, unsigned int, HLOCAL*, HLOCAL*, FARPROC, long);
typedef int(WINAPI* SPI_CONFIGRATIONDLG)(HWND, int);
typedef int(WINAPI* SPI_GETARCHIVEINFO)(LPSTR, long, unsigned int, HLOCAL*);
typedef int(WINAPI* SPI_GETFILEINFO)(LPSTR, long, LPSTR, unsigned int, LPSPI_ARCHIVEINFO);
typedef int(WINAPI* SPI_GETFILE)(LPSTR, long, LPSTR, unsigned int, LPSPI_CALLBACK, long);

#define SPIPROC_GETPLUGININFO "GetPluginInfo"
#define SPIPROC_ISSUPPORTED "IsSupported"
#define SPIPROC_GETPICTUREINFO "GetPictureInfo"
#define SPIPROC_GETPICTURE "GetPicture"
#define SPIPROC_GETPREVIEW "GetPreview"
#define SPIPROC_CONFIGRATIONDLG "ConfigurationDlg"
#define SPIPROC_GETARCHIVEINFO "GetArchiveInfo"
#define SPIPROC_GETFILEINFO "GetFileInfo"
#define SPIPROC_GETFILE "GetFile"

//=============================================================================
// EOF
//=============================================================================

#ifdef __cplusplus  // "C"宣言
}
#endif

#endif
