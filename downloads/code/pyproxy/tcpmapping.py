# -*- coding: utf-8 -*-

import socket
import time

CFG_REMOTE_IP = '127.0.0.1'
CFG_REMOTE_PORT = 8000
CFG_LOCAL_IP = '127.0.0.1'
CFG_LOCAL_PORT = 80

PKT_BUFF_MAX = 1460

# log
def send_log(content):
    print content
    return

# tcp mapping
def tcp_mapping(remote_ip, remote_port, local_ip, local_port):
    # local server
    local_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    local_server.bind((local_ip, local_port))

    send_log('Starting local server(' + local_ip + ':' + str(local_port) + ')...')

    # start listening
    local_server.listen(5)
    (local_conn, local_addr) = local_server.accept()
    local_conn.settimeout(5)
    
    # when got a local connection, start remote connect
    remote_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    remote_server.connect((remote_ip, remote_port))
    send_log('Connect to remote server(' + remote_ip + ':' + str(remote_port) + ')')
    
    try:
        while True:
            msg_request = local_conn.recv(PKT_BUFF_MAX)
            if not msg_request:
                break
            remote_server.send(msg_request)
            send_log(' Request: ' + repr(msg_request))
            while PKT_BUFF_MAX == len(msg_request):
                msg_request = local_conn.recv(PKT_BUFF_MAX)
                remote_server.send(msg_request)
                send_log(' Request: ' + repr(msg_request))

            msg_response = remote_server.recv(PKT_BUFF_MAX)
            local_conn.send(msg_response)
            send_log(' Response: ' + repr(msg_response))
            while PKT_BUFF_MAX == len(msg_response):
                msg_response = remote_server.recv(PKT_BUFF_MAX)
                local_conn.send(msg_response)
                send_log(' Response: ' + repr(msg_response))
    finally:
        remote_server.close()
        local_server.close()

    return

# main
if __name__ == '__main__':
    tcp_mapping(CFG_REMOTE_IP, CFG_REMOTE_PORT, CFG_LOCAL_IP, CFG_LOCAL_PORT)

