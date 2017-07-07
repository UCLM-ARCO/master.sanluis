from celery import Celery
from tasks import add

results = []
celery = Celery()
celery.config_from_object('celeryconfig')
 
for x in range(1,5):
	 results.append(celery.send_task("tasks.add",[4,4]))


for y in results:
         print y.get(timeout=1)
