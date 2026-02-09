#pragma once
#include "PlatformSetup.h"

// ======================== SERVER TICK ======================== //

// The server keeps a "tick" counter for timing and updates
// g_cachedTick stores the most recent tick value for quick access
extern u32 g_cachedTick;

// Returns the current cached server tick.
u32 GetCachedTick();

// ========================== PACKET ============================ //

// PROTOCOL represents the type/ID of a internal network message
typedef u16 PROTOCOL;

// Total buffer size for a packet
#define C_PACKET_BUFFER_SIZE        8912
// Space reserved for packet header
#define C_PACKET_HEADER_SIZE        4
// Actual payload space
#define C_PACKET_DATA_SIZE          (C_PACKET_BUFFER_SIZE - C_PACKET_HEADER_SIZE)