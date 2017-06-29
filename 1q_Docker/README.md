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

Docker Flow:

    Image -> ```docker run -ti image_name``` -> 
    Running Container -> ```exit``` -> 
    Stopped Container -> ```docker commit container_id``` -> 
    New Image

View running/stopped containers

```bash
docker ps -a
```

The Output is:

    - Repository -> where the image came from
    - Tag -> image version number
    - Image ID -> internal Docker representation of the image
    - Referring to the image -> repository:tag or image id

Now we need to turn the image into a running container:

```bash
# Image -> docker run -> Running Container
docker run -ti ubuntu:latest bash # terminal interactive
root@new_container: cat /etc/lsb-release
```

Let's look at the running container from outside and format the output nicer:

- Let's update .bashrc

```bash
vi ~/.bashrc
export FORMAT='\nID\t{{.ID}}\nIMAGE\t{{.Image}}\nCOMMAND\t{{.Command}}\nCREATED\t{{.RunningFor}}\nSTATUS\t{{.Status}}\nPORTS\t{{.Ports}}\nNAMES\t{{.Names}}\n'

# docker-specific
dock='sudo docker'
dockps='dock --format $FORMAT'
```

- Let's view running containers

```bash
docker ps
```

The Output is:

- ID -> container ID, different from image ID
- Image -> ubuntu:latest
- Command/Created/Ports/Names
- Status -> specify the process number we exited from. This can provide a clue to why a container exited or died.

If we stop the container, we can view the last running (-l) or all running (-a) containers:

```bash
docker ps -l
docker ps -a
```

To save the stopped container as a new image:

```bash
docker commit CONTAINER_ID # return new image's SHA
docker commit CONTAINER_ID IMAGE_NAME
docker images # the new image doesn't contain repository or tag
docker tag 59687df41cf1(ImageID) elastics(new_repository_name) # the image is tagged
docker rmi my-tag # will remove an unwated tag
docker push # push to my docker hub
```

--- 

### Run Processes in Containers
Let's now dive into what exactly happens when containers a run in Docker.

- The ```docker run image process`` gets the image name to start the container from and the process to run in that container.
- The container is not done until that process exits
- If we start other processes in that container, the container only finishes when the main process is finished (and not the other processes)
- So Docker containers have **one main** process
- Containers have names, and we don't give the name, the Docker will make on up

Some more functionality:

- Run a command or a process within the container and then delete that container on exit:

```bash
docker run --rm -ti ubuntu sleep 5 # start a container, sleep for 5 seconds, exit, rm the container
```

- Start a container, run a command in it, then run another command, then exit, and delete a container

```bash
docker run --rm -ti ubuntu bash -c "sleep 3; echo all done"
```

- Now let's talk about leaving things in a container. Docker has an idea of **detached** containers. You can have a container running and just let it go

```bash
docker run -d -ti ubuntu bash # run on the background
docker ps
docker attach container_name # to jump into the started container (ssh-like)
# Cntr + P and Cntr + Q -> to run in the background
```

- How to add another process to a running container
  - great for debugging when containers are acting out.
  - great for DB administration
  - cannot add ports, volumes, and other things that are possible with ```docker run```
  - when the original container exits the main process, the ```exec`` (child) process exits as well

```bash
docker exec -ti container_name bash # execute another process in the running container
```

---

### Manage Containers
Looking at the container output of a container that is already finished could be very frustrating. You start up a container, it didn't work, you want to know what went wrong. 

- Looking at container logs
  - The ```docker logs``` command is useful for debugging.
  - The docker keeps containers' logs as long as the container stays alive.
  - Let's test out the logs:
  - run container
  - give it a name
  - run it as detached container
  - run it based on the "ubntu" image
  - run a process bash inside the container
  - execute the command ```less /etc/password```
  - purposely misspell the command and look at the logs

  ```bash
  docker run --name example -d ubuntu bash -c "loss /etc/passord"
  docker logs example # output: lose - command not found
  ```
  - Don't let the output get too large

- Stopping and Removing Containers
  - often when trying to start a container with a fixed name, you will get an error saying that container already exists. It is because the container hasn't been removed.

  ```bash
  docker kill container_name # stop a container
  docker rm container_name  # remove a container
  ```

- Container Resource Constaints
  - One of the big features of docker is the ability to enforce limits on how many resources a container is gonna use.
    - You can limit to a fixed amount of memory, which prevents runaway containers from clobbering the rest of the sytem

  ```bash
  docker run --memory maximum-allowed-memory image_name command
  ```
    - You can limit the CPU time relative to what is available for the system (i.e. give the container half of the total CPU time, and the other container the other half, so that if one is not busy, the other can use more CPU) - but it will enforce that the containers have equal access

  ```bash
  docker run --cpu-shares # relative to other containers
  ```

    - You can also give hard limits, for example for the CPU usage: this container can only use 10% of the system's CPU, even though the other 90% are idle

  ```bash
  docker run --cpu-quota
  ```

- Orchestration
  - Most of the Orchestration systems (discussed later) generally require you to state the limists of a particular task or container.

- Lessons
  - Dont' let your containers fetch dependencies when they start. Include the dependencies inside you containers, so that any updates to the dependencies don't break the entire infrastructure (i.e. Nodejs dependencies -> don't install package.json packages on container start, but rather create the container with the dependencies)
  - Don't leave important things in unnamed stopped containers

---

### Network Between Containers
