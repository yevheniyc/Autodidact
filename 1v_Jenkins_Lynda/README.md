### Learning Jenkins
Lynda.com's introduction to Jenkins toolset.

#### Terminology
- Project or Job - a user-configured description of the work that Jenkins will manage.
    - A list of tasks that Jenkins will execute to produce desired results
- Build - what happens when Jenkins runs through the instructions in the project.
    - One run of a project
- Build Step - actual steps that Jenkins will run
    - A task inside a project: checking out source code or running a script
- Build Trigger - the event that starts the build
    - Builds can be started Manually (clicking on the Build button), or automatically
    based on a schedule
- Plugins - extensions to the core Jenkins functionality

#### Installation

1. Get the server running on the local machine:
```bash
docker pull jenkins/jenkins:lts
docker run -d -p 8080:8080 -v jenkins_home:/var/jenkins_home \
           -- name jenkins jenkins/jenkins:lts
```

2. To extract the admin password from the container:
```bash
docker exec jenkins cat /var/jenkins_home/secrets/initialAdminPassword
```
- Paste the pw into localhost:8080

3. Click on the Install Essential Plugins
4. Signup! -> new user's name/pw will be used from now on!
---
#### Jenkins UI
- New Item - new jobs
- People - people who can run jobs
- Build History - details information about past jobs
- Manage Jenkins:
    - Configure System - env vars
    - Configure Global Security - who is allowed to access and use the sytems
    - Configure Credentials - users, private keys, auth credentials for the users
    outside of the Jenkins users
    - Global Tools Configuration - configure tools, their locations and automatically
    installers
    - Manage Plugins
    - Manage Users - add/edit/delete users that can manage this Jenkins instance
- Build Queue - shows which builds are ready to be run
- Build Executor Status - what builds are running at the present moment
---
#### Manage Plugins
Go to Manage Jenkins -> Manage Plugins; Look over Azure CLI
Add global tools: Manage Jenkins -> Global Tool Configuration

#### Create Job
Click on **New Item**
