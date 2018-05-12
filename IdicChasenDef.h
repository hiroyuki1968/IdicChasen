#if !defined(IDICCHASENDEF_H__INCLUDED_)
#define IDICCHASENDEF_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define WRITEFILE
//#define YAHOOOLD
//#define YAHOOIDIC

#define HISTORY_COUNT	64

#define MAIN_EXENAME		"IdicChasen"

#define FNAME_PRODUCTCODE	"ProductCode.txt"
#define FNAME_PROFILE		MAIN_EXENAME ".INI"
#define FINDKEY_FNAME		"FindKey.txt"

#define DNAME_IDICCHASEN	"アイドル相性ランキング"

#define OLD_DNAME_HKUN		"Hashikun"

#define PF_APP_GENERAL			"General"

#define PF_KEY_VER				"Ver"
#define PF_KEY_SHOWCMD			"ShowCmd"
#define PF_KEY_WIDTH			"Width"
#define PF_KEY_HEIGHT			"Height"
#define PF_KEY_CHASEN			"Chasen"
#define PF_KEY_IDIC				"Idic"
#define PF_KEY_NAME				"Name"
#define PF_KEY_SEX				"Sex"

#define PF_KEY_BIRTHDATETIME	"BirthDateTime"
#define PF_KEY_BIRTHPREFECTURE	"BirthPrefecture"
#define PF_KEY_BIRTHLONG		"BirthLong"
#define PF_KEY_BIRTHLAT			"BirthLat"
#define PF_KEY_TIMEDIFF			"TimeDiff"
#define PF_KEY_SUMMERTIME		"SummerTime"
#define PF_KEY_DAILY			"Daily"
#define PF_KEY_OPPOSITESEX		"OppositeSex"

#define PF_KEY_YAHOO			"Yahoo"
#define PF_KEY_MINAGE			"MinAge"
#define PF_KEY_MAXAGE			"MaxAge"
#define PF_KEY_BLOODTYPEA		"BloodTypeA"
#define PF_KEY_BLOODTYPEB		"BloodTypeB"
#define PF_KEY_BLOODTYPEO		"BloodTypeO"
#define PF_KEY_BLOODTYPEAB		"BloodTypeAB"
#define PF_KEY_EXENOTES			"ExeNotes"

#define PF_KEY_YAHOOTVPEOPLE	"YahooTVPeople"

#define MUTEX_INSTANCE	"Mutex_IdicChasen_Instance"

#define ERRMSG			"%s: %s エラー"
#define ERRMSG_DETAIL	"%s: %s エラー: %s"
#define ERRMSG_MEMEX	"%s: CMemoryException エラー: %s"
#define ERRMSG_OLEEX	"%s: COleException エラー: %s"
#define ERRMSG_FILEEX	"%s: CFileException エラー: %s"
#define ERRMSG_TIMEOUT	"%s: %s %s タイムアウトエラー"
#define ERRMSG_NOTFOUND	"%s: %s が存在しません"
#define ERRMSG_NOINPUT	"%s: %s が入力されてません"

#endif // !defined(IDICCHASENDEF_H__INCLUDED_)
