from socket import *

# Setup TCP socket
serverSocket = socket(AF_INET, SOCK_STREAM)
HOST, PORT = 'localhost', 6789
serverSocket.bind((HOST, PORT))
serverSocket.listen(1)

while True:
  #Establish the connection
  print 'Ready to serve...'
  connectionSocket, addr = serverSocket.accept() #Fill in start #Fill in end

  try:
    # Receive HTTP request
    message = connectionSocket.recv(1024)
    filename = message.split()[1]
    print "trying to find file: " + filename[1:]
    f = open(filename[1:])
    outputdata = f.read()

    # Create HTTP response header
    connectionSocket.send('HTTP/1.1 200 OK\r\n')
    connectionSocket.send('Content-Type: text/html\r\n')
    connectionSocket.send('\r\n')

    # Send HTTP response
    for i in range(0, len(outputdata)):
      connectionSocket.send(outputdata[i])
    connectionSocket.close()

    # Print request granted
    print "File sent from server " + filename[1:]

  except IOError:
    #Send HTTP response message for file not found
    connectionSocket.send('HTTP/1.1 404 NOT FOUND\r\n')
    connectionSocket.send('Content-Type: text/html\r\n')
    connectionSocket.send('\r\n')
    connectionSocket.send('404 File Not Found: ' + filename[1:] + '\r\n')

    # Print error in requested file
    print "File not found " + filename[1:]

  #Close client socket
  connectionSocket.close()

serverSocket.close()
