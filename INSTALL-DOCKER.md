# Docker installation guide on Fedora :penguin:
As a first assignement of the course **Scientific Computing for Physics Students**, this is a brief guide on how to install the program **Docker** on the linux distribution **Fedora 41**. 
This guide follows one of the possible installation methods from the official [Docker](https://www.docker.com/desktop/setup/install/linux/) website.
## Docker Engine and Docker Desktop :ship:
A first remark should be made on the two possible interfaces available for Docker:\
-**Engine**: the Command Line Interface (**CLI**) to interact with the program through the Linux terminal;\
-**Desktop**: the Graphical User Interface (**GUI**) which provide a graphic environment to the user and run on top of the Engine. 
## Docker Engine :memo:
- As a prerequirement, install the ``dnf-plugins-core`` package allowing dnf to manage repositories.
>$ sudo dnf install dnf-plugins-core
- The first step is to set up on your machine the Docker repository. 
>$ sudo dnf-3 config-manager --add-repo https://download.docker.com/linux/fedora/docker-ce.repo
- Install then the latest version of docker.
>$ sudo dnf install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
>
(Verify that this ``060A 61C5 1B55 8A7F 742B 77AA C52F EB6B 621E 9F35`` is the printed key)
- Important commands to keep in mind are the following:

| Action                                 | Command                              |  
|:--------------------------------------:|:--------------------------------------:|
| Start docker                           | `$ sudo systemctl start docker`        |
| Stop docker                            | `$ sudo systemctl stop docker`         |
| Check if docker is running             | `$ sudo systemctl is-active docker`    |
| Enable docker to start on boot         | `$ sudo systemctl enable docker`       |
| Disable docker to start on boot        | `$ sudo systemctl disable docker`      |
| Check if docker is enabled             | `$ sudo systemctl is-enabled docker`   |
| Start docker now and enable it on boot | `$ sudo systemctl enable --now docker` |
| List all containers                     | `$ sudo docker ps`                     |

## Docker Desktop :whale:
- Download the package [here](https://desktop.docker.com/linux/main/amd64/docker-desktop-x86_64.rpm?utm_source=docker&utm_medium=webreferral&utm_campaign=docs-driven-download-linux-amd64). 
- Install the desktop version of Docker with the command: 
>$ sudo dnf install ./docker-desktop-x86_64.rpm
>
- Launch the program from your application browser.
# Running AlmaLinux 9 :cd:
As a simple example of Docker, here are briefly reported the principal steps to run AlmaLinux 9.
## Docker Engine
To download an image from the registry of Docker run in your terminal
> $ sudo docker pull almalinux:9
>
and then to start the container in the **background** type
> $ sudo docker run almalinux:9
> 
If you want to start the container in the **iterative** mode, which gives you an interactive shell, type
> $ sudo docker -it run almalinux:9
## Docker Desktop
- In the Desktop version search your desired distribution using the **search bar** and then press **pull** . The downloaded image is now present in your **Images** tab.
- Select the image and press **run** to open a new container. 
