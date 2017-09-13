#ifndef SERVER_H
#define SERVER_H

#pragma once

#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>

#include <QDir>
#include <QMutex>

using namespace std;
using boost::asio::ip::tcp;

class Server
{
private:
    typedef boost::shared_ptr<tcp::socket> socketPtr;
    static const unsigned short lengthBuf = 64;
    boost::asio::io_service io_service;

public:
    Server();
    Server(int port);

    static void Session(socketPtr socket);
    static void Recognition(socketPtr &socket);
    static void Registration(socketPtr &socket);
    static void CheckUser(socketPtr &socket);
};

#endif // SERVER_H
