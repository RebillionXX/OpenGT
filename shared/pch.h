#pragma once
#include "PlatformSetup.h"
#include "Util/MiscUtils.h"
#include "Util/ResourceUtils.h"

/*
#include "Network/NetworkAcceptor.h"
#include "Network/NetworkClientSocket.h"
#include "Network/NetworkPacket.h"
#include "Network/NetworkServerContext.h"
#include "Network/NetworkServerSocket.h"
#include "Network/NetworkSession.h"
#include "Network/NetworkSessionManager.h"
#include "Network/NetworkSocket.h"
*/
#include "Network/NetUtils.h"

#include "Common/CommonDef.h"
#include "Common/CommonServerDef.h"

#if defined(OPENGT_MAIN)
#include "../OpenGT.Main/App.h"
#endif

#ifdef _DEBUG
    #define     LOG_TRACE           	__LogMsg
#else
	#if defined(WINAPI)
		#define LOG_TRACE		   	 	__noop
	#else
		#define LOG_TRACE(...)			((void)0)
	#endif
#endif

#define         LOG_TRACE_LINE(X)		__LogMsg( "%s (%d) : %s", __FILE__, __LINE__, X);
#define         LOG_TRACE_FUNCTION(X, ...)	__LogMsg( "%s: " X, __PRETTY_FUNCTION__, ##__VA_ARGS__);

#ifdef _DEBUG
    #define     LOG_ERROR           	__LogError
#else
	#if defined(WINAPI)
		#define LOG_ERROR		    	__noop
	#else
		#define LOG_ERROR(...)			((void)0)
	#endif
#endif

#define         LOG_ERROR_LINE(X)		__LogError( "%s (%d) : %s", __FILE__, __LINE__, X);

#define			LOG_DEBUG(X, ...)		__LogMsg( "**DEBUG** (%s): " X, __PRETTY_FUNCTION__, ##__VA_ARGS__);