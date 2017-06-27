#### Docker Installation on Ubuntu VM (VirtualBox)

1. Add the GPG key for the official Docker repository to the system

```bash
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
```

2. Add the Docker repository to APT sources

```bash
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
```

3. Update local **apt-get** and install **Docker**

```bash
sudo apt-get update
apt-cache policy docker-ce # Output: docker-ce ...
```

4. Install the actual docker

```bash
sudo apt-get install -y docker-ce
# view docker deamon
sudo systemctl status docker # docker.service - Docker App...
```

#### Working with Docker images
1. Run and exit the docker

```bash
sdocker run hello-world
```

2. Search for docker images in Docker Hub

```bash
sdocer search ubuntu
```

3. Pull an image to local host and run it

```bash
sdocker pull ubuntu
sdocker run ubuntu
sdocker images # to view the images
```

4. Container Management

```bash
sdocker ps -a # view all containers past and present
sdocker ps -l # view the latest run container
sdocker commit -m "added vim and nodejs" -a "Tuesday yev" df78c1f9769f finid/ubuntu-nodejs
sdocker login -u yevheniyc
sdocker push yevheniyc/ubuntu-nodejs
# change tag on container
sdocker tag 206914cf980a yevheniyc/ubuntu-nodejs
```
