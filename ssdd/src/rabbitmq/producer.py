#!/usr/bin/env python
import pika

localhost = pika.ConnectionParameters(host='localhost')
connection = pika.BlockingConnection()
channel = connection.channel()

channel.basic_publish(exchange='',
                      routing_key='hello',
                      body='Hello World!')

print " [x] Sent 'Hello World!'"
connection.close()
