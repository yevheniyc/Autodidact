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
docker run hello-world
```

2. Search for docker images in Docker Hub

```bash
docker search ubuntu
```

3. Pull an image to local host and run it

```bash
docker pull ubuntu
docker run ubuntu
docker images # to view the images
```

4. Container Management

```bash
docker ps -a # view all containers past and present
docker ps -l # view the latest run container
docker commit -m "added vim and nodejs" -a "Tuesday yev" df78c1f9769f finid/ubuntu-nodejs
docker login -u yevheniyc
docker push yevheniyc/ubuntu-nodejs
# change tag on container
docker tag 206914cf980a yevheniyc/ubuntu-nodejs
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
---

### Images
Images use the same resources, so don't use **SIZE** as the accurate representation.
Turning containers into images:
```bash
docker pas -l
docker commit container_id new_image_name
docker commit container_id new_image_name:tag(version-v2.1; default=latest)
# Full Name Structure
registry.example.com:port/organization/image-name:version-tab
```
- Name Structure:
  - server where the registry resides
  - port on that registry server
  - organization
  - image name
  - version tag

```bash
docker rmi image_id
# or
docker rmi image_name
```
---

### Volumes
Volumes are virtual disks that we can store data in and share them between the containers and/or hosts. Two types of volumes:
- Persistent: data will be available on hosts even after container goes away
- Ephemeral: exists as long as a container uses them

Volumes are not part of images either you pull or push, volumes get excluded.

#### Sharing data between the Host and the Container
Sharing a folder and a file: between Linux host (virtual machine) and the containers

```bash
docker-machine ssh # if on Mac or Windows
mkdir example      # on the host
# link host's /home/greenhat/example to container's /shared-folder
docker run -ti -v /home/greenhat/example:/shared-folder ubuntu bash
# to share a file (NOTE: make sure the file exists before starting a container)
docker run -ti -v /home/greenhat/example/large-file.txt:/shared-folder/wow.txt ubuntu bash
```

#### Sharing data between Containers
- **volumes-from** - shared disks that exist only as long as they are being used

```bash
# start a container
docker run -ti -v /shared-data ubuntu bash
root@container_id: echo hello > /shared-data/data-file.txt

# start another container
docker run -ti --volumes-from sick_hopper ubuntu bash
root@container_id: ls /shared-data/
data-file.txt
exit

# start a third container
docker run -ti --volumes-from first_container_name ubuntu bash
root@container_id: ls /shared-data/
data-file.txt

# when exiting all of the containers, the shared folder disappears.
```

---

### Docker Registries
Registries:
- Manage(search and add) and distribute images
- Docker (the company) offers these for free
- We can run our own, as well
- Many companies run their own registries to make sure thier data stays safe and private


Finding Images:

```bash
docker search ubuntu
# look for Official[OK]
docker login # login into DockerHub
docker pull debian:sid
# give the image a new tag
docker tag debian:sid yevheniyc/test-image-42:v99.2
# publish to the public registry
docker push yevheniyc/test-image-42:v99.9
```

- Clean up images regulary
- Trust but varify

---

### Dockerfiles
Dockerfile:
- Small program to create an image

  ```bash
  docker build -t name-of-result /Dockerfile/location
  ```
  - The resulting image will have a name: "name-of-result"
  - "." - the Dockerfile's location
  - The resulting images will be in the local docker registry, ready to run with docker run

- Each step running in Dockerfile is cached:
  - docker will skip lines if they weren't changed since the last time we've run this dockerfile
  - put the code that we change the most at the end of the file
  - Dockerfiles are not shell scripts. We cannot start a program on one line and send the message to the next line. Each line is run and saved to the image. If we need one operation start and then the next start, they need to be on the same line.
  - Environment variables do persist accross lines, if **ENV** command is used.
  - Each line is its own call to docker run - this is were the difference between the docker file and shell scripts shows up.

#### Building Dockerfiles
Simplest Dockerfile:

```bash
vi Dockerfile

FROM busybox
RUN echo "building simple docker image"
CMD echo "Hello Container"
```
- FROM busybox: what image to start with (super tiny - ony shell in it)
- RUN ...     : create a container and inside of it RUN the echo command; save into an image
- CMD ...     : when image is started, run the folloing command (CMD)

Build from the docker file:

```bash
docker build -t hello .

# OUTPUT
Sending build context to Docker daemon 2.048 kB
Step 1 : FROM busybox
  ---> image_id (from which we are starting)
Step 2 : RUN echo "building simple docker image."
  ---> Running in container_id (intermediate container to run the echo command in)
building simple docker image
  ---> new_image_id
Removing intermediate container container_id
Step 3 : CMD echo "hello container"
  ---> Running in another_new_container_id (intermediate)
  ---> image_id (the final built image)
Removing intermediate container another_new_container_id
Successfully built image_id (final image)

# start a container from the new built image
docker run --rm hello
# OUTPUT:
hello container
```

A more interesting Dockerfile:

```bash
vi Dockefile
FROM debian:sid
RUN apt-get -y update
RUN apt-get install nano
CMD ["/bin/nano", "/tmp/notes"]

docker build -t example/nanoer
# OUTPUT: a bunch
docker run --rm -ti example/nanoer
# notes are opened
```

Another awesome example:

```bash
# build on the previous image!
vi Dockerfile
FROM example/nanoer
ADD notes.txt /notes.txt
CMD ["/bin/nano", "/notes.txt"]

docker build -t example/nanoer_2
docker run --rm -ti example/nanoer_2
```

#### Dockerfile syntax
- FROM:
  - FROM java:8 - build my image from this image
- MAINTAINER:
  - MAINTAINER FirstName LastName <email@example.com>
- RUN:
  - run the command from the shell: ```RUN unzip install.zip /opt/install/```
- ADD:
  - Adds local files
    - ADD run.sh /run.sh
  - Adds the contents of tar archives
    - ADD project.tar.gz /install/ - recognizes that it is an archive, and uncompress to the specified directory
  - Works with URLs:
    - ADD https://project.example.com/download/1.0/project.rpm /project/
- ENV:
  - Sets the environment variables both during for the duration of the Dockerfile, and those environment variables will still be set in the resulting image.
  - ENV DB_HOST=dp.production.example.com
- ENTRYPOINT and CMD
  - ENTRYPOINT specifies the beginning of the expression to use when starting your container, and lets you tack more on the end: so if the container has an ENTRYPOINT of **ls**, then anything you type when you say Docker RUN my image name wouldb be treated as arguments to the **ls** command.
  - CMD specifies the whole command to run and it gets executed in its entirety
  - Two forms in which commands can be executed:
    - Shell Form: ```nano notes.txt```
    - Exec Form: ```["/bin/nano", "nano.txt"]
- EXPOSE: maps a port into a container (similar to **-p** we used before):
  - EXPOSE 8080
- VOLUME: defines shared or ephemeral volumes
  - VOLUME ["/host/path" "/container/path/"] - map a host path into container path
  - VOLUME ["/shared-data"] - creates a volume (ephemeral) that can be inherited by later containers
  - Generally in Dockerfiles avoid using shared folders with the host, because it means that this Dockerfile will only work on your computer.
- WORKDIR: sets the directory both for the remainder of the Dockerfile and for the resulting container whe you run it. It is like typing **cd** at the beginning of every RUN expression
  - WORKDIR /install/ -> all the rest of the RUN statements will happen in the /install/ dir
- USER: sets which user the container will run as
  - USER greenhat
  - USER 1000

#### Avoid goldern images
- Include installers in your project
- Have a canonical build that builds everything completely from scratch. Don't fix a config in a container and overwrite the older image name. This becomes a golden image, an image for which we don't have a complete build
- Use small base images, such as Alpine
- Build images from Dockerfiles
- Don't leave passwords in the docker files

---

### Under the Hood

#### The program Docker
What Kernels do?
- Run directly on the hardware
- It receives/respond to messages from the hardware:
  - a new disk has been attached
  - a network packet has arrived
  - everything that goes on electrically, bubbles up to the kernel and gets dealt with
- It starts and schedules programs
- It says what's allowed to run and when, and allows to do everything else you ask at the same time
- It controls and organizes the storage devices on the computer. When you say "write to this file", kernel says "he actually means this little spot/address on the disk". It then goes and writes the data. Someone has to make this decision, and that's the role of the file system inside the kernel.
- It passes messages between programs, when two programs in a computer what to communicate. When two programs on different computers want to communicate over a network, they ask the kernel to pass a message.
- The kernel passes the message, gets it ready, sends it over to kernel on the other computer which receives the message, gets it ready for the program, and sends it to the program over there.
- It allocates resources, memory, time to actually do work on a CPU, how much network bandwidth to give to who. All of that is managed by kernel.

Docker, in place, is a program that manages the kernel! So Docker is:
- program written in Go - a great system language that allows for manageing kernel's features, which allows to build the concept of containers and images.
- Docker primary uses **cgroups** (control groups) to group processes together and give them the idea of being contained within their own little world - this is what keeps one cotnainer from interfering with another.
- It uses **namespaces** - which a feature of Linux kernel which allows it to split the networking stack, so that you have one set of addresses for one container, another set of addreses for another containers, and other addresses for things that are not in containers at all.
- It uses **copy-on-write** file systems and various other approaches to build the idea of images, to say you have this image, it doesn't change, but you can run stuff on top of it.
- So Docker allows scripting distributed systems easy, and that is why it is so popular!

Docker is devided into two programs: the Client and the Server
- These two program communicate over a socket - can be a network socket, where the client is running on one computer, and the server is running on a computer somethwere on a cloud provider across the world. Or they can be running directly on the same hardware. Or they can be running on the same hardware with the server in a virtual machine, which is the comman case for people in this course.
- In this case, the client communicates over a network and sends messages to the Docker server to say: make a container, start a container, stop a container. When the client and server are running on the same computer, they can connect through a special file called a socket. Since they can communicate through a file, and Docker can efficiently share files between hossts and containers, it means you can run the client, inside Docker itself. It's pretty easy to run the client inside one of the containers, and share the socket into that container, which allows the same messages to go through the same socket, get to the server running on the host, and do everything that it would do normally. So let's take a little look at what that looks like in practice. The idea is to get a visceral feel for what it means to control Docker through its socket.

```bash
ls -l /var/run/docker.sock # on the host
# if we write commands in a proper format to this file, that the docker server will do stuff
docker run -ti -v /var/run/docker.sock:/var/run/docker.sock docker sh
# we are running a container called docker, which allows us run other containers inside of it
$inside_docker_container: docker run -ti ubuntu bash # run a container within a container
root@container_id:
```
Explained:
- mount the file **docker.sock** on the host to the **docker.sock** in the container
- the container will be built from image **docker** which is an image provided by Docker (the company) to allow you to run Docker in Docker.
- The take from here is that a client can run containers from anywhere, as long as it is connected to the docker server.

---

### Networking and Namespaces
Docker manages networking for you to create containers. First of all, networking is divided into many layers:
- The bottom layer is how machines that are near each other or containers that are near each other actually talk directly to each other. We call this the Ethernet layer. It moves little frames of data in a local area.
- Above that, you have the Internet Protocol layer, or IP, and that's how data moves between networks and between systems in different parts of the world.
- Routing is how packets get into and out of networks. Docker takes care of setting up that for you too.
- Ports are specific programs running on a specific computer, actually listening to traffic.
- So Docker uses bridges to create virtual networks inside your computer. When you create a private network in Docker, it creates a bridge. These function like software switches. It's equivalent to having a little blue box on your desk and plugging a bunch of different wires into it. Except all of this is within your computer and you are plugging containers into it with virtual network wires. So these are used to control the Ethernet layer, containers that actually talk directly to each other.

Let's take a look at these bridges inside a running Docker system:
- In order to look into these bridges, we need a system with BRCTL (Bridge Control Program) installed, and have an access to my Docker host's networking

```bash
# Terminal 1

# gives a full access to the host's networking stack (layers) and turns off all the protections
docker run -ti --rm --net=host ubuntu:16.04 bash
root@default: apt-get update && apt-get install bridge-utils
root@default: brctl show
#OUTPUT
bridge_name    bridge_id   STP_enabled  interfaces
br-xxxx ...
docker0 ... # virtual network used by all machines in Docker
            # that don't have their own network

# after creating a new network: my-new-network bellow
brctl show
bridge_name ...
br-... ...
br-... ...
docker0 ...

```

```bash
docker network create my-new-network
# created a newtork
```

So docker moves packets between containers by creating bridges and running commands to configure your system.

In the above demo we turned off the isolation that prevents containers from messing with the host's network by passing the ```--net=host``` option:

  ```bash
  docker run --net=host options image-name command.
  ```
  - turn off for production!

#### Routing
Next layer up, is how Docker moves packets between networks and between cotnaienr and the internet. It uses the built-in firewall features of the Linux kernel, namely the IP tables command, to create firewall rules that control when packets get sent between the bridges, and thus become available to the containers that are attached to those bridges.

This whole system is commonly referred to as NAT (Network Address Translation). That means when a packet is on its way out towards the internet, you change the source address so it'll come back to you. Then, when it's on the way back in, you change the destination address so it looks like it came directly from the machine you were connecting to. Let's take a look at how Docker accoplishes port-forwarding under the hood: ```sudo iptables -n -L -t nat```

```bash
# Terminal 1

# ssh into docker host - not for me :)
sudo iptables -n -L -t nat # list table network address translation

#OUTPUT
...
Chain DOCKER (2 references)
target   prot  opt  source      destination
RETURN   all   --   0.0.0.0/0    0.0.0.0
# - not much informaiton

# After executing Terminal 2
sudo iptables -n -L -t nat

# OUTPUT
Chain Docker (2 reference)
target ....
...
DNAT (Destination NAT Rule) tcp dpt:8080 to:172.17.0.2:8080
```

```bash
# Terminal 2

# let's do some port-forwarded
docker run -ti -p 8080:8080 ubuntu bash
root@container_id:
```

The **Terminal 1** after creating port-forwarding rule with **Terminal 2** states the following: ```tcp dpt:8080 to:172.17.0.2:8080```
- For this machine, all traffic on port 8080 should be redirected to the address of the Docker machine (host) I just started on port 8080

That's how Docker actually accomplishes exposing a port in the container. It uses these firewall rules. So exposing a port is really port forwarding.

####Namespaces
Namespaces are a feature in the Linux kernel that allows you to provide complete network isolation to different processes in the system. So it enforces the rule that you're not allowed to mess with the networking of other processes. Processes running in containers are attached to virtual network devices. And those virtual network devices are attached to bridges, which lets them talk to any other containers attached to the same bridges. This is how it creates the virtual networking. But each container has its own copy of all of the Linux networking stack. All of the different pieces that make up the networking are isolated to each container, so that they can't do things like reach in and reconfigure other containers. Namespaces enforce the rules of Docker and keep containers safe from each other.

### Processes and cgroups
One of Docker's jobs is to manage the processes in containers, keep them isolated and keep them talking to each other where appropriate.

First, a little primer on processes in Linux:
- Processes come from other processes. It's a parent-child relationship, just one parent though.
- When a process exits, it returns that package to the process that started it.
- There's a special process, Process Zero, called init. That's the process that starts it all and every other process in a Linux system comes from dividing that process into other processes.

So in Docker, your container starts with one process, the init process. That process can divide into other processes and do any number of things. Often, it starts with a shell, and that shell splits off and runs commands and runs other processes. When that init process exits, your container just vanishes. Any other processes that were in it at the time that the init process exits get shuts down unceremoniously. The container is done!

Let's examine some of these processes:

```bash
# Terminal 1
docker run -ti --rm --name hello ubuntu bash
```

- Let's look up the process id of the init process in that container:
  - use **docker inspect** - a very powerful tool for doing docker scripting

```bash
# Terminal 2
docker inspect --format '{{.State.Pid}}' hello
# Main Process ID
13646
docker-machine ssh
sudo kill 13646 # Terminal 1 is finished!
```

- **init** cleans up abandoned processes

#### Process Isolation
Docker keeps the containers from messing with each other. It uses a feature of the Linux kernel called **cgroups** (control groups). This allows for all of the processes within a cgroup to become their own isolated place. It is used to partition your system into a set of processes that can see each other. The processes that started within this group and the children of these processes stay in this group.

, I'm gonna ssh into the Docker host so we can compare the processes seen on the system to the processes seen within that container. Linux has a special file system called /proc. It's short for slash process. Every process on this computer gets a directory in this folder listing all sorts of information about it.

So if on the host I say ls /proc, I see tons of processes, they scrolled right off the screen. Each of these numbered directories in the left window is the process ID of one process running on the system. Now I'm gonna go into my container and do the same thing, ls /proc. So in this container we can see that at the time I ran ls /proc, we had exactly two processes running in this container. No other process was at all visible.

Those two processes are one, the init process, the shell, and the second one is the ls process itself that is running while it's printing these out. The important part to take away is it's very hard to mess with the process if you can't get to its /proc entry. This provides pretty strong isolation and security between containers.


#### Resource Limiting
All right, another feature and a very important job of Docker is to control access to the limited resources on the machine.

That's the amount of time the CPU can spend doing things, and the amount of memory that can be allocated between containers. These limitations are inherited, and this is very important. If a container is given a certain amount of memory and CPU time, no matter how many processes it starts, the sum total of all those processes can't exceed the quota that was given to the initial process. They can split it up differently amongst themselves however they'd like, but you can't escape your limits by starting more processes in order to consume more limits.

---

### Storage
Unix Storage in Brief

Monting directories on top of one another - we are not copying here, but layering a directory on top of antoher:

```bash
# use -o bind for dir-on-dir mounting
sudo mount -o bind other-work work

# to look at that layering
df -a # show all of the mounted file systems, including bind-ed

# unmounting the dir will show the original files - the concept of layering!!!
sudo umount work
```

This layering (mounting/unmounting) is the key concept that allows for creating multiple images from the original image, while keeping only the diffs (the spots), and not the entire container (the cow)! This is how Docker does the shared folders between the containers and the host.

Now let's talk briefly about how Docker accomplishes the idea of images and containers. How does it do the storage behind them keeping them isolated, letting them be stacked on top of each other? All of that stuff requires a little bit of an introduction to the layers of the Unix file systems method. So at the very lowest level, you have actual things. Stuff that stores bits, hard drives, thumb drives, network storage devices.

Things where you can set a value to one or zero, and it will remember it, and you can come back later and get it. The kernel manages these. On top of those, it forms them into logical groups, so you can say these four groups form a RAID array, or these two drives should be treated as one drive, or this one drive should be treated as 432 drives, so it has a layer that lets it sort of partition up drives arbitrarily into groups and then partition those groups up. Docker makes extensive use of this capability.

On top of that, we have filesystems. That determines which bits on the drive are part of which part of which file, so the fourth byte in the file foo.txt would be at a particular spot on a particular drive, and it's up to the kernel with the filesystems to keep track of where that spot actually is. Now on top of all that, you can take programs, and programs can pretend to be filesystems. We call this FUSE filesystems.

So with that in mind, the secret to Docker and all of its images is COWs, all about COWs. COW is an acronym in this case for copy on write. So we start with our base image. This is a cow. He has no spots. Now, I want to write some spots for this cow. Let's give him some dark spots. You know, good traditional cow spots. Instead of writing directly onto the cow, 'cause someone else might be working with this cow, there might be another container running off of this image right now.

I don't want to just reach in and write some spots onto that image because someone else is probably using it, so I write my spots onto a separate layer right next to it, and then when I start my container, layer the spots over the cow and give that to the container, so the container sees the image of a cow with spots even though the cow image still exists without his spots, and others that are still using the spotless cow image can continue to do so, but I want these dark spots.

You know, somebody else really has a more artistic perspective, and they'd like a cow with light spots, so they're going to start with the same image, literally the same image, not a copy of the image, but the same one, and they're going to make their own layer, but with their own interpretation of what cow spots should look like, so they make their own filesystem layer and layer it over that image, and here we have a cow with different colored spots, so it's called copy on write when I would write to this cow instead of writing directly to the cow, I write to my own layer, which gets layered on top of the cow.

When I want to look at the cow, I just look at the whole thing. I only copy the pieces that I write. I read from the original and copy when you write. Copy on write. So to get a little bigger perspective, we have the original image of the cow, unchanged, just one of them. I'm going to draw him down here. We have the resulting images of that cow. Each one has a different set of spots layered on top of it, so we have a total of one, two, three images here, and two combinations of the way they're layered.

Docker has many different actual internal mechanisms that it uses for managing the COW layers, the copy on write filesystem layers, and these depend a lot on what's available on the system it's running on. Sometimes it uses Btrfs, sometimes it uses LVM, the logical volume manager, sometimes it uses the overlay filesystem. There are many ways. It doesn't really matter as long as it can accomplish layering on its own sort. You don't have to worry about the format of a COW on one machine, a copy on write filesystem, if you want to import that image to another one because what it does it that it takes each layer, splits out the layers, and makes them into normal gzip files and ships them over the network to you separately, and the receiving end of that network connection, the place you're actually running the Docker server, receives all of those layers separately, and then puts them together using the filesystems that are available on that computer, so this is how COWs can move easily between computers, so the containers are independent of their storage engine.

I can send images between machines pretty much freely. There is one little bit depending on the storage layer that's in use on a particular machine. It is possible in some cases to run out of layers. Some of the storage engines have a limited number of layers and others don't. If you make a very deeply nested image on a machine that allows a great number of layers, and then you package it up and try to download it on a machine that uses a storage engine with less layers, you can run out of layers.

This is worth being vaguely aware of. It doesn't come up very often, and it's good to be able to recognize it when it does. Another part of images and storage in Docker is how we do volumes and shared folders with the host. These are not actually magic. They're built right in to the Linux file system, so the Linux file system starts with an assumed root directory called slash. Everything is slash something, slash home, slash Arthur, slash Etsy, slash config file, they all start with slash.

Slash is the root of the tree where it all starts, and you attach devices to various points along that tree. You can also take a directory from anywhere in the file system tree and just attach it somewhere else right on top of what's there. Let's take a look at that. In order to take a look at this, I'm going to ssh in to the Docker host again. Let's make it a directory called example. Go in there, cd example.

Nothing here. Make a directory called work. Go into work. And let's make some files. I'm going to make six files called a, b, c, d, e, and f. Take a look. There we have our files. We go up one level and make another directory called other-work, and go into other-work.

And I'm going to make four files here called other-a, other-b, other-c, and other-d. Okay, if I do ls -R, print it all out, I see I have work and other-work. Other-work has other-a, other-b, other-c, other-d. Work has a, b, c, d, e, f. So there's our starting point. Now I'm going to do sudo mount other-work right on top of work. So I'm going to say sudo mount -o bind, bind mount is the name for the process of mounting one directory on top of another.

Other-work onto work. Alright, now let's take a look in work. Ah, I have other-a, other-b, other-c, and other-d. If I do the ls -R again, I see I still have two directories, other-work and work. Other-work has other-a, other-b, other-c, other-d, same as before. Work now has the same files.

I didn't copy them. I just layered one set of files on top of the other. In fact, we can take a look at that layering if we run df -a. Df shows the mounted filesystems, and -a says show all of them even the bind mounts. And way down here at the bottom, we see that I have home docker example work mounted right there and a bunch of other stuff. I didn't delete them, I didn't copy over them, they're still there.

There's just another directory mounted on top of them right now. When I unmount it, they'll come right back again. sudo umount work, umount is for unmount. Now we take a look. Everything is exactly the way it was. I just had temporarily put one filesytem layer over another, and then I pulled it off, revealing the original. This is how Docker does the shared folders between a container and the host, so there's an important side effect of this, which is you have to get the mount order correct.

If you want to mount a folder and then a particular file within that folder, you have to it in that order. If you mount the file so it bind mounts that file right onto that position, and then you mount a folder on top of it, the file will be underneath the folder and will be hidden, so it's important to get the order of the -v for volume arguments to Docker correct. Another bit is mounting volumes always mounts the host's filesystem over the guest.

Docker doesn't give you a way of saying mount this guest file system into the host, preserving what was on the guest. It always chooses to mount the host filesystem over the guest filesystem.

### Registries in Detail
Run Docker registry in Docker

```bash
# if container goes down, restart right away
docker run -d -p 5000:5000 --restart=always --name registry registry:2

# let's tag a container and push it to the local registry
docker tag ubuntu:14.04 localhost:5000/mycompany/my-ubuntu:99
docker push localhost:5000/mycompany/my-ubuntu:99
# this allows me to keep a copy of the ubuntu version, independantly of what happens to
# it in the official registry
```

#### Storage
We can store images either on the same machine where the registry is running, in the public registry, in S3, or saved on my local machine:

```bash
# save to the output from image(s)
docker save -o my-images.tar.gz debian:sid busybox ubuntu:14.04

# to check if the registry works
docker rmi debian:sid busybox ubuntu:14.04

# load from the registry
docker load -i my-images.tar.gz
docker images # they are back!
```

### Intro to Orchestration
Orchestration Systems:
- Start containers, restart if they fail
- Allow containers to find each other -> Service Discovery
- Make sure containers run in the place with enough resurces

The easiest to start with:
- Docker Compose:
  - single machine coordination
  - designed for testing and development
  - included in docker toolbox

- Kubernetes:
  - containers as usually
  - pods group containers together
  - services that make pods discoverable by others, etc.
  - labels
  - kubectl - make scripting large operations possible
  - flexible overlay networking
  - runs well on your hardware or a cloud provider
  - built-in service discovery

- EC2 Container Service (ECS)
  - Task definistion (analogous to a pod) - define a task that will run
  - Taks: a bunch of containers that run together
  - Services and exposes it to the Net: ensures that a task i running all the time
  - Ties into ELBs
  - Create your own instances, and once the instances are running, you can start an agent in them that will join the instance(s) to the cluster
  - pass the docker control socket into the agent
  - provides docker repos - can run your own
  - Containers(tasks) can be part of CloudFormation stacks!

Now let's briefly touch on how large systems are being built using Docker today. So just to start with, one container is about as useful as one hand clapping. It's cool, it's philosophically neat, maybe you can get something out of it, but most people want more. There are many options out there for orchestrating large systems of Docker containers. We're just going to touch on a few, and give you a place to start. Orchestration systems, start your containers, keep them running, and restart them if they fail.

They allow the containers to find each other. If a container gets restarted, all the machines that were connecting to it need to be able to find its replacement. So service discovery is a big part of any Docker orchestration system. And making sure that the containers are running in a place where the resources exist for them to actually do their job. Is the storage they need available at that location? Is there enough RAM, is there enough CPU? Is that machine being taken offline for maintenance? Does this container need to be moved somewhere else? So the easiest to get started with, and the simplest, is Docker Compose.

For single machine coordination, this is the de facto standard. In fact, you already have it on your computer. It's designed for testing, development, staging, generally working on projects that have more than one container, but not for serving them in large scale systems, and not for things that's scaled dynamically. What it does, is it brings up all your containers and volumes, et cetera, with one command. You just run Docker Compose up, and it starts all your containers. And the great feature is that it's already included in Docker Tool Box, so if you're Windows or Mac, and following this course, you already have it installed.

To learn more and to get started, head on over to the documentation page for it. And in the Getting Started section, there's a nice little tutorial. Now for larger systems, there are many choices. I'm going to touch on a couple of them here and talk about how to compare them. Kubernetes brings a couple of ideas that are fairly common, to all of the orchestration systems but expressed differently everywhere. It has containers, which run programs. Those are containers in the way that we usually think of them. Pods are groups of containers that are intended to be run together always on the same system.

So pods give you approximately as much as Docker Compose, but it's dynamically distributed, Kubernetes finds a place to run it, and it provides orchestration and service discovery and all the other stuff around these pods. Kubernetes has the idea of services, which make pods discoverable by others, accessible to others. If a connection to a pod, that's part of a service, gets restarted somewhere, then that service will redirect the traffic to the new instance.

Kubernetes has an amazingly powerful system of labels for describing every aspect of your system. So you can say, my service needs to connect to an instance of version 5.2 running on this hardware, and I need an instance that is in the same data center as this other service, it's very extensive. The kubectl command makes scripting large operations in Kubernetes, if not easy, possible to the extent that other systems don't. It gives you sort of a one command interface to do almost everything with Kubernetes.

And it provides a very flexible system of overlay networking to allow your containers to find each other and connect to each other, regardless of how things move around throughout your infrastructure. Kubernetes runs equally well on your own hardware or on a cloud provider or even across both of these. It's overlay networking system is quite well suited to a wide variety of deployment scenarios. And it has service discovery built in. To get started, head on over to Kubernetes.io, head over to the documentation page, and click on get started.

Another great option is the Amazon EC2 Container Service, or ECS. This service uses an analogous vocabulary, but with a slight different twist to each part. Task definitions provide all the information required to start a container and a set of containers that are designed to run together. It's somewhat analogous to a pod, a little bit, in Kubernetes it's all the information required for services that will run together on the same machine.

It doesn't actually run anything, creating a task definition just defines a task that will run. When a task definition is actually run, it's called a task, and that's a bunch of containers that are running right now, shared together on a single host. Services take tasks, expose them to the net as a whole, and ensure that they stay up all the time. So you'd create a service that has 14 copies of a particular task, and it will ensure that that many copies is running all the time, even if it has to split it across several hosts.

ECS has a bunch of advantages too, it ties into the existing Amazon infrastructure very well. So Amazon load balancers tie into ECS services to make your traffic available to the internet using the existing systems. You create your own instances in AWS, you have lots of control over that. And once you've got your instances running, you run an agent on them and cause them to join the cluster. This is kind of cool, because you take the Docker Control Socket, pass it to the agent that you run in Docker, and that allows the agent to control the host that it's running on.

It's kind of a neat system that makes running EC2 clusters very convenient from an operational perspective. ECS provides a set of docker repos built in. So you don't have to run your own repo, ECS has them built in and they're made available to the machines on ECS. It's perfectly easy to run your own repo along with ECS, you don't have to use the built in one if you already have your own. Containers and tasks can be part of CloudFormation stacks, which makes deployment along with other resources in AWS, very, very easy.

So if you have containers that need to access to queues, and they need access to EC2 volumes, you can deploy all of this in one go and have it be cleaned up together when the service ends. To get started with ECS, head on over to the Amazon ECS product page, and click on getting started. These are just a few of the current orchestration systems, and it's an area that's evolving rapidly. New orchestration products for Docker are being announced fairly regularly these days. And it's a good space to keep an eye on.
