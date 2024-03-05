# TCP/IP Server Application using WinSock API

## Overview
This project implements a server application in C++ using the Windows Socket API (WinSock). It is designed to listen for incoming client connections on a specified port, accept client requests, and facilitate message exchanges between the server and connected clients.

## Features
- Listen for incoming connections on port 55555.
- Accept client connection requests.
- Receive messages from clients and display them.
- Send acknowledgment messages back to clients.

## Requirements
- Windows operating system
- Visual Studio or any C++ compiler with support for WinSock API

## Setup and Compilation
1. Ensure the WinSock2.h library is included in your project settings.
2. Compile the server application using your preferred C++ compiler. For Visual Studio, create a new project and add the provided source file.

## Running the Server
1. Open the command line and navigate to the directory containing the compiled executable.
2. Run the executable. The server will start and begin listening for connections on port 55555.
3. To terminate the server, close the command line window or press CTRL+C.
