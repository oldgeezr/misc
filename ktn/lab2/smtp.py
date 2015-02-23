from socket import *
import time

endmsg = '\r\n.\r\n'

mailserver = ('smtp.stud.ntnu.no', 25)
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect(mailserver)

recv = clientSocket.recv(1024)
print "S: ",
print recv
if recv[:3] != '220':
  print "ERROR: ",
  print '220 reply not received from server.'

heloCommand = 'HELO Alice\r\n'
print "C: ",
print heloCommand
clientSocket.send(heloCommand)

recv = clientSocket.recv(1024)
print "S: ",
print recv
if recv[:3] != '250':
  print "ERROR: ",
  print '250 reply not received from server.'

mailfrom = 'MAIL FROM: <chriram@stud.ntnu.no>\r\n'
print "C: ",
print mailfrom
clientSocket.send(mailfrom)

recv = clientSocket.recv(1024)
print "S: ",
print recv
if recv[:3] != '250':
  print "ERROR: ",
  print '250 reply not received from server.'

rcptto = 'RCPT TO: <chriram@stud.ntnu.no>\r\n'
print "C: ",
print rcptto
clientSocket.send(rcptto)

recv = clientSocket.recv(1024)
print "S: ",
print recv
if recv[:3] != '250':
  print "ERROR: ",
  print '250 reply not received from server.'

data= 'DATA\r\n'
print "C: ",
print data
clientSocket.send(data)

recv = clientSocket.recv(1024)
print "S: ",
print recv
if recv[:3] != '354':
  print "ERROR: ",
  print '354 reply not received from server.'

# Message Header
clientSocket.send('From: "Christoffer" <chriram@stud.ntnu.no>\r\n')
clientSocket.send('To: "Christoffer" <chriram@stud.ntnu.no>\r\n')
clientSocket.send('Date: ' + time.strftime("%c") + '\r\n')
clientSocket.send('Subject: Test message\r\n')
clientSocket.send('\r\n')
# Message Body
clientSocket.send('This message body is sent from Christoffer!\r\n')
clientSocket.send(endmsg)

recv = clientSocket.recv(1024)
print "S: ",
print recv
if recv[:3] != '250':
  print "ERROR: ",
  print '250 reply not received from server.'

quit= 'QUIT\r\n'
print "C: ",
print quit
clientSocket.send(quit)

recv = clientSocket.recv(1024)
print "S: ",
print recv
if recv[:3] != '221':
  print "ERROR: ",
  print '221 reply not received from server.'

clientSocket.close()
print "Connection closed"
