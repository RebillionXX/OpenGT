#pragma once

#define	MAX_PROTOCOL_BASE_VALUE     64

enum PROTOCOL_BASE_VALUE
{
    // ***
    // *** increase the value by units of 0x0100 ***
    // ***

    // PROTOCOL_VALUE_BASE                             = 0x0100,
    PROTOCOL_VALUE_LOGIN							= 0x0100,
    PROTOCOL_VALUE_ASC								= 0x0200,
    PROTOCOL_VALUE_MESSAGE							= 0x0300,
};

enum Protocol_Login
{
	PROTOCOL_LOGIN						        = PROTOCOL_VALUE_LOGIN,

	PROTOCOL_LOGIN_REQ,                         // Logon -> Trans
	PROTOCOL_LOGIN_ACK,                         // Trans -> Logon -> Game
};

enum Protocol_Asc
{
	PROTOCOL_ASC							    = PROTOCOL_VALUE_ASC, 

	PROTOCOL_ASC_CONFIRMATION_REQ,				// After connecting, the first message sent is to indicate whether the sender is a server or a user
	PROTOCOL_ASC_CONFIRMATION_ACK,

    PROTOCOL_ASC_STATE_REQ,                     // Request for ASC state (Client -> Server)
    PROTOCOL_ASC_STATE_ACK,                     // Response with ASC state (Server -> Client)

    PROTOCOL_ASC_CONFIG_RELOAD_REQ,             // Request to reload ASC configuration (Client -> Server)
    PROTOCOL_ASC_CONFIG_RELOAD_ACK,             // Response for ASC configuration reload (Server -> Client)
}; 

enum Protocol_Message
{
    PROTOCOL_MESSAGE                            = PROTOCOL_VALUE_MESSAGE,

    PROTOCOL_MESSAGE_BROADCAST_REQ,             // Request to broadcast message on speficy server/player (Game -> Messenger)
    PROTOCOL_MESSAGE_BROADCAST_ACK,             // Response for message broadcast (Messenger -> Game)
};