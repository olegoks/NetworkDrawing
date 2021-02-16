#pragma once
#ifndef TCPIPSERVER_HPP
#define TCPIPSERVER_HPP

#include <string>
#include <any>

#include "ServerTypes.hpp"
#include "ConnectionInterface.hpp"

EXPIMP class TcpIpServer{
private:

	std::any implementation_;

public:

	EXPIMP explicit CALLBACK TcpIpServer(const Port port, error_code& error)noexcept(true);
	EXPIMP CALLBACK ~TcpIpServer()noexcept(true);
	EXPIMP error_code CALLBACK Start()noexcept(true);
	EXPIMP error_code CALLBACK Stop()noexcept(true);
	EXPIMP bool CALLBACK IsRunning()const noexcept(true);
	EXPIMP void CALLBACK InitProcessConnectionPacketsFunction(ProcessConnectionPacketsFunction process_connection_packets)noexcept(true);
	EXPIMP void CALLBACK InitProcessConnectionFunction(ProcessConnectionFunction process_connection)noexcept(true);
	EXPIMP void CALLBACK InitProcessConnectionCreating(ProcessConnectionFunction process_connection_creating)noexcept(true);

	EXPIMP void CALLBACK InitProcessConnectionClosing(ProcessConnectionFunction process_connection_closing)noexcept(true);
	EXPIMP Port CALLBACK PortNumber(error_code& const error)const noexcept(true);
	EXPIMP std::string CALLBACK IpAddress(error_code& const error)const noexcept(true);
	EXPIMP Number CALLBACK NumberOfConnections()const noexcept(true);

};

#endif //TCPIPSERVER_HPP
