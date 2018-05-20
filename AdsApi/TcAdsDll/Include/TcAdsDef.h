///////////////////////////////////////////////////////////////////////////////
// This is a part of the Beckhoff TwinCAT ADS API
// Copyright (C) Beckhoff Automation GmbH
// All rights reserved.
////////////////////////////////////////////////////////////////////////////////


#ifndef __ADSDEF_H__
#define __ADSDEF_H__

#ifndef	ANYSIZE_ARRAY
#define	ANYSIZE_ARRAY					1
#endif

#define	ADS_FIXEDNAMESIZE				16

////////////////////////////////////////////////////////////////////////////////
// AMS Ports
#define	AMSPORT_LOGGER					100
#define	AMSPORT_R0_RTIME				200
#define	AMSPORT_R0_TRACE				(AMSPORT_R0_RTIME+90)
#define	AMSPORT_R0_IO					300
#define	AMSPORT_R0_SPS					400
#define	AMSPORT_R0_NC					500
#define	AMSPORT_R0_ISG					550
#define	AMSPORT_R0_PCS					600
#define	AMSPORT_R0_PLC					801
#define	AMSPORT_R0_PLC_RTS1				801
#define	AMSPORT_R0_PLC_RTS2				811
#define	AMSPORT_R0_PLC_RTS3				821
#define	AMSPORT_R0_PLC_RTS4				831
#define	AMSPORT_R0_PLC_TC3				851

////////////////////////////////////////////////////////////////////////////////
// ADS Cmd Ids
#define ADSSRVID_INVALID					0x00
#define ADSSRVID_READDEVICEINFO				0x01
#define ADSSRVID_READ         				0x02
#define ADSSRVID_WRITE        				0x03
#define ADSSRVID_READSTATE    				0x04
#define ADSSRVID_WRITECTRL    				0x05
#define ADSSRVID_ADDDEVICENOTE  			0x06
#define ADSSRVID_DELDEVICENOTE  			0x07
#define ADSSRVID_DEVICENOTE					0x08
#define ADSSRVID_READWRITE      			0x09

////////////////////////////////////////////////////////////////////////////////
// ADS reserved index groups
#define ADSIGRP_SYMTAB						0xF000
#define ADSIGRP_SYMNAME						0xF001
#define ADSIGRP_SYMVAL						0xF002

#define ADSIGRP_SYM_HNDBYNAME				0xF003
#define ADSIGRP_SYM_VALBYNAME				0xF004
#define ADSIGRP_SYM_VALBYHND				0xF005
#define ADSIGRP_SYM_RELEASEHND				0xF006
#define ADSIGRP_SYM_INFOBYNAME				0xF007
#define ADSIGRP_SYM_VERSION					0xF008
#define ADSIGRP_SYM_INFOBYNAMEEX			0xF009

#define ADSIGRP_SYM_DOWNLOAD				0xF00A
#define ADSIGRP_SYM_UPLOAD					0xF00B
#define ADSIGRP_SYM_UPLOADINFO				0xF00C
#define ADSIGRP_SYM_DOWNLOAD2				0xF00D
#define ADSIGRP_SYM_DT_UPLOAD				0xF00E
#define ADSIGRP_SYM_UPLOADINFO2				0xF00F

#define ADSIGRP_SYMNOTE						0xF010		// notification of named handle

#define ADSIGRP_SUMUP_READ					0xF080		// AdsRW  IOffs list size or 0 (=0 -> list size == WLength/3*sizeof(ULONG))
																	// W: {list of IGrp, IOffs, Length}
																	// if IOffs != 0 then R: {list of results} and {list of data}
																	// if IOffs == 0 then R: only data (sum result)
#define ADSIGRP_SUMUP_WRITE					0xF081		// AdsRW  IOffs list size
																	// W: {list of IGrp, IOffs, Length} followed by {list of data}
																	// R: list of results
#define ADSIGRP_SUMUP_READWRITE				0xF082		// AdsRW  IOffs list size
																	// W: {list of IGrp, IOffs, RLength, WLength} followed by {list of data}
																	// R: {list of results, RLength} followed by {list of data}
#define ADSIGRP_SUMUP_READEX				0xF083		// AdsRW  IOffs list size
																	// W: {list of IGrp, IOffs, Length}
#define ADSIGRP_SUMUP_READEX2				0xF084		// AdsRW  IOffs list size
																	// W: {list of IGrp, IOffs, Length}
																	// R: {list of results, Length} followed by {list of data (returned lengths)}
#define ADSIGRP_SUMUP_ADDDEVNOTE			0xF085		// AdsRW  IOffs list size
																	// W: {list of IGrp, IOffs, Attrib}
																	// R: {list of results, handles}
#define ADSIGRP_SUMUP_DELDEVNOTE			0xF086		// AdsRW  IOffs list size
																	// W: {list of handles}
																	// R: {list of results, Length} followed by {list of data}

#define ADSIGRP_IOIMAGE_RWIB				0xF020		// read/write input byte(s)
#define ADSIGRP_IOIMAGE_RWIX				0xF021		// read/write input bit
#define ADSIGRP_IOIMAGE_RISIZE				0xF025		// read input size (in byte)
#define ADSIGRP_IOIMAGE_RWOB				0xF030		// read/write output byte(s)
#define ADSIGRP_IOIMAGE_RWOX				0xF031		// read/write output bit
#define ADSIGRP_IOIMAGE_CLEARI				0xF040		// write inputs to null
#define ADSIGRP_IOIMAGE_CLEARO				0xF050		// write outputs to null
#define ADSIGRP_IOIMAGE_RWIOB				0xF060		// read input and write output byte(s)

#define ADSIGRP_DEVICE_DATA					0xF100		// state, name, etc...
#define ADSIOFFS_DEVDATA_ADSSTATE			0x0000		// ads state of device
#define ADSIOFFS_DEVDATA_DEVSTATE			0x0002		// device state



////////////////////////////////////////////////////////////////////////////////
// ADS Return codes
#define ADSERR_NOERR						0x00
#define	ERR_ADSERRS							0x0700

#define ADSERR_DEVICE_ERROR					(0x00+ERR_ADSERRS) // Error class < device error >
#define ADSERR_DEVICE_SRVNOTSUPP			(0x01+ERR_ADSERRS) // Service is not supported by server
#define ADSERR_DEVICE_INVALIDGRP 			(0x02+ERR_ADSERRS) // invalid indexGroup
#define ADSERR_DEVICE_INVALIDOFFSET			(0x03+ERR_ADSERRS) // invalid indexOffset
#define ADSERR_DEVICE_INVALIDACCESS			(0x04+ERR_ADSERRS) // reading/writing not permitted
#define ADSERR_DEVICE_INVALIDSIZE			(0x05+ERR_ADSERRS) // parameter size not correct
#define ADSERR_DEVICE_INVALIDDATA			(0x06+ERR_ADSERRS) // invalid parameter value(s)
#define ADSERR_DEVICE_NOTREADY				(0x07+ERR_ADSERRS) // device is not in a ready state
#define ADSERR_DEVICE_BUSY					(0x08+ERR_ADSERRS) // device is busy
#define ADSERR_DEVICE_INVALIDCONTEXT		(0x09+ERR_ADSERRS) // invalid context (must be InWindows)
#define ADSERR_DEVICE_NOMEMORY				(0x0A+ERR_ADSERRS) // out of memory
#define ADSERR_DEVICE_INVALIDPARM			(0x0B+ERR_ADSERRS) // invalid parameter value(s)
#define ADSERR_DEVICE_NOTFOUND				(0x0C+ERR_ADSERRS) // not found (files, ...)
#define ADSERR_DEVICE_SYNTAX				(0x0D+ERR_ADSERRS) // syntax error in comand or file
#define ADSERR_DEVICE_INCOMPATIBLE			(0x0E+ERR_ADSERRS) // objects do not match
#define ADSERR_DEVICE_EXISTS				(0x0F+ERR_ADSERRS) // object already exists
#define ADSERR_DEVICE_SYMBOLNOTFOUND		(0x10+ERR_ADSERRS) // symbol not found
#define ADSERR_DEVICE_SYMBOLVERSIONINVALID	(0x11+ERR_ADSERRS) // symbol version invalid
#define ADSERR_DEVICE_INVALIDSTATE			(0x12+ERR_ADSERRS) // server is in invalid state
#define ADSERR_DEVICE_TRANSMODENOTSUPP		(0x13+ERR_ADSERRS) // AdsTransMode not supported
#define ADSERR_DEVICE_NOTIFYHNDINVALID		(0x14+ERR_ADSERRS) // Notification handle is invalid
#define ADSERR_DEVICE_CLIENTUNKNOWN			(0x15+ERR_ADSERRS) // Notification client not registered
#define ADSERR_DEVICE_NOMOREHDLS			(0x16+ERR_ADSERRS) // no more notification handles
#define ADSERR_DEVICE_INVALIDWATCHSIZE		(0x17+ERR_ADSERRS) // size for watch to big
#define ADSERR_DEVICE_NOTINIT				(0x18+ERR_ADSERRS) // device not initialized
#define ADSERR_DEVICE_TIMEOUT				(0x19+ERR_ADSERRS) // device has a timeout
#define ADSERR_DEVICE_NOINTERFACE			(0x1A+ERR_ADSERRS) // query interface failed
#define ADSERR_DEVICE_INVALIDINTERFACE		(0x1B+ERR_ADSERRS) // wrong interface required
#define ADSERR_DEVICE_INVALIDCLSID			(0x1C+ERR_ADSERRS) // class ID is invalid
#define ADSERR_DEVICE_INVALIDOBJID			(0x1D+ERR_ADSERRS) // object ID is invalid
#define ADSERR_DEVICE_PENDING				(0x1E+ERR_ADSERRS) // request is pending
#define ADSERR_DEVICE_ABORTED				(0x1F+ERR_ADSERRS) // request is aborted
#define ADSERR_DEVICE_WARNING				(0x20+ERR_ADSERRS) // signal warning
#define ADSERR_DEVICE_INVALIDARRAYIDX		(0x21+ERR_ADSERRS) // invalid array index
#define ADSERR_DEVICE_SYMBOLNOTACTIVE		(0x22+ERR_ADSERRS) // symbol not active -> release handle and try again
#define ADSERR_DEVICE_ACCESSDENIED			(0x23+ERR_ADSERRS) // access denied
#define ADSERR_DEVICE_LICENSENOTFOUND		(0x24+ERR_ADSERRS) // no license found
#define ADSERR_DEVICE_LICENSEEXPIRED		(0x25+ERR_ADSERRS) // license expired
#define ADSERR_DEVICE_LICENSEEXCEEDED		(0x26+ERR_ADSERRS) // license exceeded
#define ADSERR_DEVICE_LICENSEINVALID		(0x27+ERR_ADSERRS) // license invalid
#define ADSERR_DEVICE_LICENSESYSTEMID		(0x28+ERR_ADSERRS) // license invalid system id
#define ADSERR_DEVICE_LICENSENOTIMELIMIT	(0x29+ERR_ADSERRS) // license not time limited
#define ADSERR_DEVICE_LICENSEFUTUREISSUE	(0x2A+ERR_ADSERRS) // license issue time in the future
#define ADSERR_DEVICE_LICENSETIMETOLONG		(0x2B+ERR_ADSERRS) // license time period to long
#define ADSERR_DEVICE_EXCEPTION				(0x2C+ERR_ADSERRS) // exception in device specific code
#define ADSERR_DEVICE_LICENSEDUPLICATED		(0x2D+ERR_ADSERRS) // license file read twice
#define ADSERR_DEVICE_SIGNATUREINVALID		(0x2E+ERR_ADSERRS) // invalid signature
#define ADSERR_DEVICE_CERTIFICATEINVALID	(0x2F+ERR_ADSERRS) // public key certificate
//
#define ADSERR_CLIENT_ERROR					(0x40+ERR_ADSERRS) // Error class < client error >
#define ADSERR_CLIENT_INVALIDPARM			(0x41+ERR_ADSERRS) // invalid parameter at service call
#define ADSERR_CLIENT_LISTEMPTY				(0x42+ERR_ADSERRS) // polling list	is empty
#define ADSERR_CLIENT_VARUSED				(0x43+ERR_ADSERRS) // var connection already in use
#define ADSERR_CLIENT_DUPLINVOKEID			(0x44+ERR_ADSERRS) // invoke id in use
#define ADSERR_CLIENT_SYNCTIMEOUT			(0x45+ERR_ADSERRS) // timeout elapsed
#define ADSERR_CLIENT_W32ERROR				(0x46+ERR_ADSERRS) // error in win32 subsystem
#define ADSERR_CLIENT_TIMEOUTINVALID		(0x47+ERR_ADSERRS) // ?
#define ADSERR_CLIENT_PORTNOTOPEN			(0x48+ERR_ADSERRS) // ads dll
#define ADSERR_CLIENT_NOAMSADDR				(0x49+ERR_ADSERRS) // ads dll
#define ADSERR_CLIENT_SYNCINTERNAL			(0x50+ERR_ADSERRS) // internal error in ads sync
#define ADSERR_CLIENT_ADDHASH				(0x51+ERR_ADSERRS) // hash table overflow
#define ADSERR_CLIENT_REMOVEHASH			(0x52+ERR_ADSERRS) // key not found in hash table
#define ADSERR_CLIENT_NOMORESYM				(0x53+ERR_ADSERRS) // no more symbols in cache
#define ADSERR_CLIENT_SYNCRESINVALID		(0x54+ERR_ADSERRS) // invalid response received
#define ADSERR_CLIENT_SYNCPORTLOCKED		(0x55+ERR_ADSERRS) // sync port is locked

#pragma	pack( push, 1)
typedef struct AmsNetId_
{
	unsigned char b[6];

} AmsNetId, *PAmsNetId;

typedef struct
{
	AmsNetId	netId;
	unsigned short port;
} AmsAddr, *PAmsAddr;

typedef	struct
{
	unsigned char		version;
	unsigned char		revision;
	unsigned short		build;
} AdsVersion;

typedef	AdsVersion*	PAdsVersion;

////////////////////////////////////////////////////////////////////////////////
typedef enum nAdsTransMode
{
	ADSTRANS_NOTRANS		= 0,
	ADSTRANS_CLIENTCYCLE	= 1,
	ADSTRANS_CLIENTONCHA	= 2,
	ADSTRANS_SERVERCYCLE	= 3,
	ADSTRANS_SERVERONCHA	= 4,
}ADSTRANSMODE;

typedef enum nAdsState
{
	ADSSTATE_INVALID			= 0,
	ADSSTATE_IDLE				= 1,
	ADSSTATE_RESET				= 2,
	ADSSTATE_INIT				= 3,
	ADSSTATE_START				= 4,
	ADSSTATE_RUN				= 5,
	ADSSTATE_STOP				= 6,
	ADSSTATE_SAVECFG			= 7,
	ADSSTATE_LOADCFG			= 8,
	ADSSTATE_POWERFAILURE		= 9,
	ADSSTATE_POWERGOOD			= 10,
	ADSSTATE_ERROR				= 11,
	ADSSTATE_SHUTDOWN			= 12,
	ADSSTATE_SUSPEND			= 13,
	ADSSTATE_RESUME				= 14,
	ADSSTATE_CONFIG				= 15,
	ADSSTATE_RECONFIG			= 16,
	ADSSTATE_STOPPING			= 17,
	ADSSTATE_MAXSTATES
} ADSSTATE;

typedef struct
{
	unsigned long	cbLength;
	ADSTRANSMODE	nTransMode;
	unsigned long	nMaxDelay;
	union
	{
		unsigned long		nCycleTime;
		unsigned long		dwChangeFilter;
	};
} AdsNotificationAttrib, *PAdsNotificationAttrib;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned	long	hNotification;
	__int64				nTimeStamp;
	unsigned	long	cbSampleSize;
	unsigned	char	data[ANYSIZE_ARRAY];
} AdsNotificationHeader, *PAdsNotificationHeader;

////////////////////////////////////////////////////////////////////////////////

#define	ADSNOTIFICATION_PDATA( pAdsNotificationHeader )	\
	(	(unsigned char*)	(((PAdsNotificationHeader)pAdsNotificationHeader->data )


////////////////////////////////////////////////////////////////////////////////
typedef void (__stdcall *PAdsNotificationFuncEx)(	AmsAddr*	pAddr,
													AdsNotificationHeader* pNotification,
													unsigned long hUser
													);

////////////////////////////////////////////////////////////////////////////////
#define	ADSSYMBOLFLAG_PERSISTENT		0x00000001
#define	ADSSYMBOLFLAG_BITVALUE			0x00000002
#define	ADSSYMBOLFLAG_REFERENCETO		0x0004
#define	ADSSYMBOLFLAG_TYPEGUID			0x0008
#define	ADSSYMBOLFLAG_TCCOMIFACEPTR		0x0010
#define	ADSSYMBOLFLAG_READONLY			0x0020
#define	ADSSYMBOLFLAG_CONTEXTMASK		0x0F00

////////////////////////////////////////////////////////////////////////////////
// ADS data types
typedef char					ADS_INT8;
typedef unsigned char			ADS_UINT8;
typedef short					ADS_INT16;
typedef unsigned short			ADS_UINT16;
typedef long					ADS_INT32;
typedef unsigned long			ADS_UINT32;
typedef __int64					ADS_INT64;
typedef unsigned __int64		ADS_UINT64;
typedef float					ADS_REAL32;
typedef double					ADS_REAL64;
typedef long double				ADS_REAL80;


////////////////////////////////////////////////////////////////////////////////
// ADS symbol information
typedef struct
{
	unsigned	long		entryLength;	// length of complete symbol entry
	unsigned	long		iGroup;			// indexGroup of symbol: input, output etc.
	unsigned	long		iOffs;			// indexOffset of symbol
	unsigned	long		size;			// size of symbol ( in bytes, 0 = bit )
	unsigned	long		dataType;		// adsDataType of symbol
	unsigned	long		flags;			// see above
	unsigned	short		nameLength;		// length of symbol name (excl. \0)
	unsigned	short		typeLength;		// length of type name (excl. \0)
	unsigned	short		commentLength;	// length of comment (excl. \0)
} AdsSymbolEntry, *PAdsSymbolEntry, **PPAdsSymbolEntry;


#define	PADSSYMBOLNAME(p)			((char*)(((PAdsSymbolEntry)p)+1))
#define	PADSSYMBOLTYPE(p)			(((char*)(((PAdsSymbolEntry)p)+1))+((PAdsSymbolEntry)p)->nameLength+1)
#define	PADSSYMBOLCOMMENT(p)		(((char*)(((PAdsSymbolEntry)p)+1))+((PAdsSymbolEntry)p)->nameLength+1+((PAdsSymbolEntry)p)->typeLength+1)

#define	PADSNEXTSYMBOLENTRY(pEntry)	(*((unsigned long*)(((char*)pEntry)+((PAdsSymbolEntry)pEntry)->entryLength)) \
						? ((PAdsSymbolEntry)(((char*)pEntry)+((PAdsSymbolEntry)pEntry)->entryLength)): NULL)



////////////////////////////////////////////////////////////////////////////////
#define	ADSDATATYPEFLAG_DATATYPE		0x00000001
#define	ADSDATATYPEFLAG_DATAITEM		0x00000002

#define	ADSDATATYPE_VERSION_NEWEST		0x00000001

typedef struct
{
	unsigned	long		lBound;
	unsigned	long		elements;
} AdsDatatypeArrayInfo, *PAdsDatatypeArrayInfo;

typedef struct
{
	ADS_UINT32		entryLength;	// length of complete datatype entry
	ADS_UINT32		version;			// version of datatype structure
	union {
	ADS_UINT32		hashValue;		// hashValue of datatype to compare datatypes
	ADS_UINT32		offsGetCode;	// code offset to getter method
	};
	union {
	ADS_UINT32		typeHashValue;	// hashValue of base type
	ADS_UINT32		offsSetCode;	// code offset to setter method
	};
	ADS_UINT32		size;			// size of datatype ( in bytes )
	ADS_UINT32		offs;			// offs of dataitem in parent datatype ( in bytes )
	ADS_UINT32		dataType;		// adsDataType of symbol (if alias)
	ADS_UINT32		flags;			//
	ADS_UINT16		nameLength;		// length of datatype name (excl. \0)
	ADS_UINT16		typeLength;		// length of dataitem type name (excl. \0)
	ADS_UINT16		commentLength;	// length of comment (excl. \0)
	ADS_UINT16		arrayDim;		//
	ADS_UINT16		subItems;		//
	// ADS_INT8		name[];			// name of datatype with terminating \0
	// ADS_INT8		type[];			// type name of dataitem with terminating \0
	// ADS_INT8		comment[];		// comment of datatype with terminating \0
	// AdsDatatypeArrayInfo	array[];
	// AdsDatatypeEntry		subItems[];
	// GUID			typeGuid;		// typeGuid of this type if ADSDATATYPEFLAG_TYPEGUID is set
	// ADS_UINT8	copyMask[];		// "size" bytes containing 0xff or 0x00 - 0x00 means ignore byte (ADSIGRP_SYM_VALBYHND_WITHMASK)
} AdsDatatypeEntry, *PAdsDatatypeEntry, **PPAdsDatatypeEntry;

#define	PADSDATATYPENAME(p)			((PCHAR)(((PAdsDatatypeEntry)p)+1))
#define	PADSDATATYPETYPE(p)			(((PCHAR)(((PAdsDatatypeEntry)p)+1))+((PAdsDatatypeEntry)p)->nameLength+1)
#define	PADSDATATYPECOMMENT(p)		(((PCHAR)(((PAdsDatatypeEntry)p)+1))+((PAdsDatatypeEntry)p)->nameLength+1+((PAdsDatatypeEntry)p)->typeLength+1)
#define	PADSDATATYPEARRAYINFO(p)	(PAdsDatatypeArrayInfo)(((PCHAR)(((PAdsDatatypeEntry)p)+1))+((PAdsDatatypeEntry)p)->nameLength+1+((PAdsDatatypeEntry)p)->typeLength+1+((PAdsDatatypeEntry)p)->commentLength+1)

__inline PAdsDatatypeEntry AdsDatatypeStructItem(PAdsDatatypeEntry p, unsigned short iItem)
{
	unsigned	short i;
	PAdsDatatypeEntry	pItem;
	if ( iItem >= p->subItems )
		return NULL;
	pItem = (PAdsDatatypeEntry)(((unsigned char*)(p+1))+p->nameLength+p->typeLength+p->commentLength+3+p->arrayDim*sizeof(AdsDatatypeArrayInfo));
	for ( i=0; i < iItem; i++ )
		pItem = (PAdsDatatypeEntry)(((unsigned char*)pItem)+pItem->entryLength);
	return pItem;
}

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned	long	nSymbols;
	unsigned	long	nSymSize;
} AdsSymbolUploadInfo, *PAdsSymbolUploadInfo;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned	long		nSymbols;
	unsigned	long		nSymSize;
	unsigned	long		nDatatypes;
	unsigned	long		nDatatypeSize;
	unsigned	long		nMaxDynSymbols;
	unsigned	long		nUsedDynSymbols;
} AdsSymbolUploadInfo2, *PAdsSymbolUploadInfo2;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	unsigned	long	indexGroup;
	unsigned	long	indexOffset;
	unsigned	long	cbLength;
} AdsSymbolInfoByName, *PAdsSymbolInfoByName;

////////////////////////////////////////////////////////////////////////////////
// AMS events
typedef enum nAmsRouterEvent
{
	AMSEVENT_ROUTERSTOP		= 0,
	AMSEVENT_ROUTERSTART	= 1,
	AMSEVENT_ROUTERREMOVED	= 2
}AmsRouterEvent;

typedef void (*PAmsRouterNotificationFunc)( long nEvent );
typedef void  ( __stdcall *PAmsRouterNotificationFuncEx)( long nEvent );

////////////////////////////////////////////////////////////////////////////////

#pragma	pack( pop )

#endif	// __ADSDEF_H__
