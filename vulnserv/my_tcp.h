/**
 * @file my_tcp.h
 * Header file for a simple TCP socket interface using the Winsock library.
 * Designed to abstract common operations in TCP communication such as socket
 * creation, binding, listening, accepting connections, and data reception.
 *
 * Social Media Links:
 * https://twitter.com/7etsuo
 * https://github.com/7etsuo
 * https://www.youtube.com/@snowcrash
 *
 * Social Media Links:
 * - Twitter: https://twitter.com/7etsuo
 * - GitHub: https://github.com/7etsuo
 * - YouTube: https://www.youtube.com/@snowcrash-
 *
 * Author: 7etsuo, 2024
 */

#ifndef MY_TCP_H
#define MY_TCP_H

#include <winsock2.h>

#define PORT 12345
#define BUFFER_SIZE 1024

/**
 * Structure to hold socket information for server and client communication.
 */
typedef struct _SOCKET_T
{
  SOCKET listenSocket;
  SOCKET clientSocket;
} SOCKET_T;

/**
 * Structure to hold data received from a client.
 */
typedef struct _RCV_DATA_T
{
  char data[BUFFER_SIZE];
  SIZE_T n_read;
} RCV_DATA_T;

/**
 * Structure to represent a client connection, bundling socket and received
 * data.
 */
typedef struct _CLIENT_CONNECTION_T
{
  SOCKET_T *sockets;
  RCV_DATA_T *client_data;
} CLIENT_CONNECTION_T;

/**
 * Receives data from a client connection.
 * @param client A pointer to CLIENT_CONNECTION_T struct holding client info.
 * @param max_read Maximum number of bytes to read.
 * @return Number of bytes read, SOCKET_ERROR on failure.
 */
int RecvData (CLIENT_CONNECTION_T *client, SIZE_T max_read);

/**
 * Closes and cleans up Winsock operations for a client connection.
 * @param client A pointer to CLIENT_CONNECTION_T struct holding client info.
 */
void CloseWinsock (CLIENT_CONNECTION_T *client);

/**
 * Accepts a client connection on a listening socket.
 * @param listenSocket The listening socket.
 * @return A SOCKET for the accepted client connection.
 */
SOCKET AcceptClientConnection (SOCKET listenSocket);

/**
 * Listens for incoming connections on a specified socket.
 * @param listenSocket The socket to listen on.
 * @param port The port number to bind to for listening.
 * @return 0 if successful, SOCKET_ERROR otherwise.
 */
int DoListen (SOCKET listenSocket, int port);

/**
 * Binds a socket to a local address and port.
 * @param listenSocket The socket to bind.
 * @return 0 if successful, SOCKET_ERROR otherwise.
 */
int BindSocket (SOCKET listenSocket);

/**
 * Creates a new socket for TCP communication.
 * @return A SOCKET object if successful, INVALID_SOCKET otherwise.
 */
SOCKET CreateSocket (void);

/**
 * Initializes Winsock DLLs required for network operations.
 */
void InitWinsock (void);

#endif // MY_TCP_H
