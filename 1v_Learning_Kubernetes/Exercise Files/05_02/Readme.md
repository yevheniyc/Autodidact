# Running the Kubernetes Dashboard

## Chapter Goals
1. Run the Kubernetes Dashboard in minikube
2. Explore the dashboard and look for the features it supports
3. Create a deployment from the dashboard

### Run the Kubernetes Dashboard in minikube
The Kubernetes Dashboard is a simple, web user interface for Kubernetes clusters. It allows users to manage applications running in the cluster and troubleshoot them, as well as manage the cluster itself.

One of the common asks in the container world is for the need for a ui to visualize what is going on with clusters. It was one of the most requested features of Docker when it first started, and companies like StackEngine, the one I worked at, or Rancher, were the way devops engineers would use to manage clusters.

Kubernetes learned from this lesson early on, and created the Kubernetes Dashboard for this purpose, and it allows you to monitor and view clusters from an operational perspective.

We will also enable heapster, to see cluster memory and CPU usage. This is enabled on minikube with `minikube addons enable heapster`

The dashboard comes pre enabled as an addon. To start up the dashboard type `minikube dashboard` in your command prompt.


This will bring up the dashboard in your browser.


### 2. Explore the dashboard and look for the features it supports
Explore the cluster sections, available namespaces.

Visit the deployments section, and drill down into a deployment, and notice how you can scale, edit or delete a deployment. Visit the replica set for the deployment to see all the pods associated with it.

Go into the pod section to see all the pods running. Notice how you can fetch pod logs from the ui directly, or exec into a pod if it has it available.

### 3. Create a deployment from the dashboard
Create a helloworld deployment with the UI; specify an app name, and container image karthequian/helloworld:latest with 2 pods. See the deployment and pods running in the UI.

#### Handout Links

[Dashboard - Full Featured Web Interface for Kubernetes] http://blog.kubernetes.io/2016/07/dashboard-web-interface-for-kubernetes.html