###Amazon Web Services Essential Training - Lynda
***
#####Cloud Services
** Infrastructure as a Service (IaaS)
  ** Windows Asure
  ** Rackspace Cloud
** Platform as a Service (PaaS)
  ** Google App Engine
  ** PHP Fog
  ** Heroku
** Software as a Service (SaaS)
  ** Google Apps
  ** Basecamp
  ** Mint

** AWS offers all three services (IaaS, PaaS, Saas)
***
#####Business Benefits
** Minimal upfront infrastructure investment
** Just in-time infrastructure - expand based on my needs
** Maximize efficiency of resources
** Only pay for what you use

#####Technical Benefits
** Have APIs for scriptable automations 
** Automatically scale my system Up/Down Right/Left
** Meet anticipated demand
** Ease of implementing disaster recovery infrastructure

#####Scalable Architectures (up/down/in/out)
** Scaling Out (horizontal scaling) - adding capacity to a system by adding more components or nodes that make up that system. For example, adding more web servers to the system to handle an increase in traffic.
** Scaling In (horizontal scaling) - removing capacity from a system, by decreasing the number of components or nodes. For example, scale in the web server tier by reducing the number of running web servers.
** Scaling Up (vertical scalling) - adding resources to a single component or node in our system in order to increase cits capacity to handle load. For example, increasing the number of CPUs or increase the memory of a database server. 
** Scaling Down (vertical scalling) - reducing the resources of a single component or node in the system. 

#####Understanding Elasticity
** Clouds ability to accomodate changes in load and demand of the system.

Examples of restructuring:
- There is not a Cloud server type that has the exact or greater amount of RAM required on single server, that what you already have on premises. In that case, you should think about ways to distribute that need across multiple servers, by rethinking you application architecture, or perhaps by leveraging other available Cloud services, like a distributed memory cache (i.e. AWS EsastiCache).
- You find that the database requires more input/output operations per second, often referred to as IOPS, than what the Cloud provides. There are other ways to achieve this, based on your data in use cases. One solution is to distribute across a cluster, thereby scaling out the database layer, or take advantage of other database sharding techniques that can route data and requests to where they need to be. 
- Often, if you find to be hitting constraints with Cloud infrastructure (which in theory is infinitely scalable), this is most likely due to the application architecture not being built in a scalable manner. 



