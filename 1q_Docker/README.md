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

6. Docker-Machine

- Install and run Docker on Mac or Windows
- Provision and manage multiple remote Docker hosts
- Provision Swarm Clusters
- Starts up a linux virtual machine that manages the containers



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

Private Container Networking:

- Docker provides a private network for use by the containers on your system
- Programs in containers are isolated from the Internet by default. Containers can have several private networks, so that you can isolate things nicely.
  - We can group our containers into "private" networks, so that all of our stuff related to one infrastructure is in one private network, and an unrelated service doesn't have to worry about interfering with that or being snopped upon.
- We explicitly set, when running Docker, who can talk to whom and on what ports, and this is done by explicitly **exposing ports** and **linking containers**.
- Docker has a good mechaism for helping these containers find each other and make the connections.
- Docker helps you find other exposed ports with Compose services.

Exposing a Specific Port: for incoming connections

- Explicitly specify the port inside the container that can be excessed by outside container
- We can do this for as many ports as we want per container

Example:

- Let's start up a container -> ```docker run```
- Let's clean up the container after exit -> ```-rm``
- Let's make it interactive terminal -> ```-ti```
- Let's assing a port to it -> ```-p 45678:45678```
  - expose port **45678** inside the container
  - to the outside of the container as port **45678**
  - So this says that I want the program listening on port **45678** inside the container to reachable from outside the container by just going to that host on port **45678**, and then it will be forwarded to the container and the connection will be established.
- Let's **forward** another port to this containers -> ```-p 45679:45679```
- So now both ports **45678** and **45679** forward connections directly in the container.
- Let's name this container -> ```--name echo-server```
- Lets run this container from image -> ```ubuntu:14.04```
- Let's start a bash process in the container -> ```bash```
- Once inside the conainer, let's build an echo server with **netcat** -> ```nc -lp 45678``` 
  - At this point anyone who connects to the port 45678 will be able to echo messages
- Let's add a relay to the echo server -> ```nc -lp 45678 | nc -lp 45679```
  - Anything passed into port 45678 will be piped out of port 45679 

  ```bash
  docker run -rm -ti -p 45678:45678 -p 45679:45679 --name echo-server ubuntu:14.04 bash
  root@container_id:/# nc -lp 45678 # netcat listen to port 45678
  ```
- Let's test and see how this container relays information:
  - first, Docker Machine starts up a Linux virtual machine on the computer, to run the actual containers. So we need to find out what is the IP address of that machine so that we can connect to the port we've just opened. 
  - second, we netcat to both ports:
    - terminal 1: ```nc IP 45678```
    - terminal 2: ```nc IP 45679```
  - no the messages in terminal 1 will be relayed to terminal 2 via the container

Exposing Ports Dynamically:
- Docker has a command that finds exposed ports, which helps to resolve conflicts in advance, in case we want to create a container on a port that is being used. IMPORTANT!
- The program inside the container always listens on the same port, but from the outside of the container, it just gets whatever port is next available:
  - Let's start a container with specified exposed internal ports, but dynamically exposed external
  ```bash
  docker run --rm -ti -p 45678 -p 45679 --name echo-server ubuntu:14.04 bash
  ```
  - To examine which external ports were dynamically assigned: ```docker port container_name```
  ```bash
  # output:
  45678/tcp -> 0.0.0.0:45678
  45679/tcp -> 0.0.0.0:45679
  ```
  - This is often used with a service discovery program that manages hooking up the machines outside docker
  - Note: by default docker opens up TCP ports, if UDP port needs to be open:
  ```bash
  docker run -p outside-port:inside-port/protocol
  ```

---

### Link Containers
Connecting data between containers

First approach:
- Connecting between containers via Host Network. Communicate data from Client to Server Containers by exposing a port on each of the containers and then having each of them connect to the host on that port, which then gets forwarded to the appropriate container. For example:
  - Expose a particular port from the host 1234:1234 into this container:
  ```bash
  docker run -ti --rm -p 1234:1234 -name server-listener ubuntu:14.04 bash
  root@container_id:/# nc -lp 1234 # listen to connection on port 1234
  ```
  - Get the IP address of the virtual machine that runs docker and containers:
  ```bash
  $ ifconfig # within virtualbox -> will show docker0 interface and IP 
  ```
  - Now, start up another container -> client container and connect out to the host (use above IP) on port 1234, which is redirected to the server-listener container:
  ```bash
  docker run -ti --rm ubuntu:14.04 -name client-listener bash
  root@container_id:/# nc host_IP 1234
  hello world # redirected -> to server-listener
  ```
Second approach:
- Connecting directly between containers using Virtual Network. Link container directly, so that data travels from server to client container while staying within Docker. This apprach has advantages and a few things to watch out for.
- This approach is usually used with some orchestration tool to keep track of what's running where.
- When two containers are linked, all their ports are linked, but only one way. You are connecting from the client to the server, but the server doesn't know when a client connects to it or goes away - so it is one way
- This should be used on the services that are meant to be running on the same machine. A good example is a service and a health check that monitors it. A service and its DB - not a good example:
  
  ```bash
  # start up a server
  docker run --rm -ti --name server ubuntu:14.04 bash
  root@container_id:/# nc -lp 1234
  ```
  ```bash
  # start up a client
  docker run --rm -ti --link server --name client ubuntu:14.04 bash
  root@container_id:/# nc server 1234
  hello # -> will reflect in the server container
  ```
  - the act of linking creates a name within this container to refer to the server, or the machine the client is linked to, which happens to be named server here. So we can connect directly to the server by using: ```nc server 1234```
  - when creating a client, docker added the "server" to: ```cat /etc/hosts```
  - if the server's IP address changes after that, the link will break

- How to make Links not break when the services start and stop?
  - Docker has private networks that you can set up, put containers in, and that will keep track of the names at the network level, so that when containers go away and come back, the name will change for all of the machines in that private network to refer to the new address.
  - You have to make these networks in advance. It's not fully automatic, but it's pretty easy.
  - Create private networks within Docker:
  
  ```bash
  # terminal 1
  docker network create example
  docker run --rm -ti --net=example --name server ubuntu:14.04 bash
  root@container_id:/# nc -lp 1234
  ```
  ```bash
  # terminal 2
  docker run --rm -ti --link server --net=example --name client ubuntu:14.04 bash
  root@container_id: nc server 1234
  hello # will reflect in terminal 1
  # terminate container in terminal 1 and start again.
  # creating a new container with the same name (server), still allows client
  #+to link to the server, because their on the same private network.
  ```

NOTE: 
- Linking through private networks is relatively new to Docker. Before they had a feature called linking, which was very similar, but it worked by setting environment variables inside the containers.
- IP Address Binding in Your Services:
  - Very often a service is configured to either listen for connections from the local machine of from the internet. Now when that service gets moved into a containe, the local machine for that container's perspective is the inside of that container. If you wanted to actually be able to receive connections from the same host, but in different containers, you need to change that service to listen for connections from the internet, by setting its bind address to **0.0.0.0**
  - You will see this a lot when configuring web servers and the such. Don't worry about exposing, as you can still use Docker to limit access to only from the same host. You just have to allow access from outside the container into the container. Example:
    - Listen for connections only from the localhost address 127.0.0.1
    - and only if it's coming from this host should you forward it on port 1234
    - into the container on port 1234 using TCP
  ```bash
  docker run -p 127.0.0.1:1234:1234/tcp
  ```
 

