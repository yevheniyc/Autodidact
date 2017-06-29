### Quick Start
The below section is a quick reference describing docker setup. The entire tutorial follows Lynda's "Learning Docker" tutorial.

#### Docker Installation on Ubuntu VM (VirtualBox)

1. Add the GPG key for the official Docker repository to the system. This will allow APT to trust packages signed by Docker.

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
# allows to securily install packages from docker package archive
sudo apt-get install apt-transport-https ca-certificate
```

4. Install the actual docker

```bash
sudo apt-get install -y docker-ce
# view docker deamon
sudo systemctl status docker # docker.service - Docker App...
```

5. Add a user to Docker group

```bash
sudo usermod -aG docker greenhat
``` 

#### Working with Docker images
1. Run and exit the docker

```bash
sdocker run hello-world
```

2. Search for docker images in Docker Hub

```bash
sdocker search ubuntu
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

---

### Docker Flow

Docker Image - just enough of the OS to do what we need to do. This allows us to run multiple of these images on a single computer. Tranditionally, however, we would install an OS with all sorts of packages, whether we needed them or not. 

```bash
docker ps -a
```

The Output is:

- Repository -> where the image came from
- Tag -> image version number
- Image ID -> internal Docker representation of the image

Now we need to turn the image into a running container:

```bash
# Image -> docker run -> Running Container
docker run -ti ubuntu:latest bash
cat /etc/lsb-release
```

Let's look at out running container from outside

```bash
docker ps
```

The Output is:

- ID -> container ID, different from image ID
- Image -> ubuntu:latest
- Command/Created/Status/Ports/Names


