#pragma once

#ifndef TCPIPCLIENT_HPP
#define TCPIPCLIENT_HPP

#include <string>

#include "ServerTypes.hpp"
#include "Packet.hpp"
#include "ConnectionInterface.hpp"

using ImplementationPointer = void*;

EXPIMP class TcpIpClient{
private:

	ImplementationPointer implementation_;

public:

	EXPIMP CALLBACK TcpIpClient(error_code& const error)noexcept(true);
	EXPIMP CALLBACK ~TcpIpClient()noexcept(true);

	EXPIMP error_code CALLBACK Connect(const std::string& const ip, const Port port)noexcept(true);
	EXPIMP error_code CALLBACK Disconnect()noexcept(true);
	EXPIMP error_code CALLBACK Start()noexcept(true);
	EXPIMP error_code CALLBACK Stop()noexcept(true);
	EXPIMP error_code CALLBACK Send(const Packet& const packet)const noexcept(true);

	EXPIMP void CALLBACK InitProcessConnectionPacketsFunction(ProcessConnectionPacketsFunction process_packet);
	EXPIMP void CALLBACK InitProcessConnectionCreatingFunction(ProcessConnectionFunction process_connection_creating)noexcept(true);
	EXPIMP void CALLBACK InitProcessConnectionFunction(ProcessConnectionFunction process_connection)noexcept(true);
	EXPIMP void CALLBACK InitProcessConnectionClosingFunction(ProcessConnectionFunction process_closing)noexcept(true);


};

#endif //TCPIPCLIENT_HPP
