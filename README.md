# goodnight

Daemon ensuring children go to bed in time

Copy goodnight.service to /etc/systemd/system/goodnight.service

Set path to goodnight executable in goodnight.service
```
sudo systemctl daemon-reload
sudo systemctl enable goodnight.service
sudo systemctl start goodnight.service
```
