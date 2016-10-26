###Amazon Web Services Essential Training - Lynda
***
#####Cloud Services

- Infrastructure as a Service (IaaS)
 - Windows Asure
 - Rackspace Cloud
    
- Platform as a Service (PaaS)
 - Google App Engine
 - PHP Fog
 - Heroku
 
- Software as a Service (SaaS)
 - Google Apps
 - Basecamp
 - Mint

AWS offers all three services (IaaS, PaaS, Saas)

#####Business Benefits

- Minimal upfront infrastructure investment
- Just in-time infrastructure - expand based on my needs
- Maximize efficiency of resources
- Only pay for what you use

#####Technical Benefits

- Have APIs for scriptable automations 
- Automatically scale my system Up/Down Right/Left
- Meet anticipated demand
- Ease of implementing disaster recovery infrastructure

#####Scalable Architectures (up/down/in/out)

- Scaling Out (horizontal scaling) - adding capacity to a system by adding more components or nodes that make up that system. For example, adding more web servers to the system to handle an increase in traffic.
- Scaling In (horizontal scaling) - removing capacity from a system, by decreasing the number of components or nodes. For example, scale in the web server tier by reducing the number of running web servers.
- Scaling Up (vertical scalling) - adding resources to a single component or node in our system in order to increase cits capacity to handle load. For example, increasing the number of CPUs or increase the memory of a database server. 
- Scaling Down (vertical scalling) - reducing the resources of a single component or node in the system. 

#####Understanding Elasticity
Clouds ability to accomodate changes in load and demand of the system.

Examples of restructuring:

- There is not a Cloud server type that has the exact or greater amount of RAM required on single server, that what you already have on premises. In that case, you should think about ways to distribute that need across multiple servers, by rethinking you application architecture, or perhaps by leveraging other available Cloud services, like a distributed memory cache (i.e. AWS EsastiCache).
- You find that the database requires more input/output operations per second, often referred to as IOPS, than what the Cloud provides. There are other ways to achieve this, based on your data in use cases. One solution is to distribute across a cluster, thereby scaling out the database layer, or take advantage of other database sharding techniques that can route data and requests to where they need to be. 
- Often, if you find to be hitting constraints with Cloud infrastructure (which in theory is infinitely scalable), this is most likely due to the application architecture not being built in a scalable manner. 


#####Design for Failure

- Avoid single points of failure (2 web servers -> 1 database server) - using Relational Database Service (RDS)

#####Implement Elasticity - ability to scale cloud resource up/down/in/out

- Scale on regular bases: daily/monthly/weekly - highly predictable traffic
- Just when expecting event to happend: due to some events
- Setup monitoring infrastructure (i.e. CPU utilization, or Network IO) - based on this info scale appropriately/automatically

- Automate your deployment process
- insure that initial system configuration and how you guild your applications are streamlined to accomodate scalling
- Bootstrapping instances 
    - refers to creating a self-sustaining start-up process that can run on its own and in the context of AWS
    - tipically involves the process neeed to get your application up and running on an EC2 instance
    
#####Loose Coupling

- Minimize dependencies between components
- Example infrastructure: several web servers, app servers and a database server

- Tightly-coupled components:
<br><img src="img/1_tight_coupling.png" width="200" hight="200">
- Loosely-coupled components
<br><img src="img/2_loose_coupling.png" width="200" hight="200">

#####Security

- Provider (AWS) Responsibility
    - Physical security of the building
    - Infrastructure security
    - Equipment security
    - Keeping customers separate

- My Responsibility
    - Network level
    - Application level

- Keep Things Secure
    - Protect the data in motion: 
        - Use SSL for transmitting confidential information
        - SSL certificates could be created per-instance on EC2
        - SSL certificates could be created per-load-balancer - which is a preferable option when supporting multiple applications
	- SSL certification could be created/configured via AWS
    - Protect the data at rest:
        - Encrypt data before storing it on any storage devices
        - Encrypt the entire file storage systems. In AWS file storage comes in 2 different variaties:
    	    - Elastic block storage - persists beyond the lifetime of the underlying instance - **encryptable**
	    - Local storage - will not servive the termination of the instance on which it presides - **encryptable**
	    - Store/Encrypt data in other AWS stores as well
        - Protect AWS access credentials - AWS supplies two types of security credentials:
	    - AWS Access Keys - has two parts to it:
		- A public access key ID
		- A secret key ID: 
                    - when using the APIs, use secret key ID for request authentication
                    - all public API requests sent via the internet should be sent over HTTPS
                    - if your application uses other AWS services, which require your secret key, rather than having your secret key be part of the applicaiton code, you should build your applications in a manner such that this secret key is passed in as arguments during launch of the application. The secret key should also be encrypted before sending.
                    - you can also launch your instance in IAM role - allows an instance to have access to the credentials associated with that role.
                        - IAM role - AWS's service designed so that your applications can securely make API requests from your instances, without requiring you to manage the security credentials that the applications use. Instead of creating and distributing your AWS credentials, you can delegate permission to make API requests using IAM roles. IAM is also used to manage access control: it allows you to create users and manage their permissions by assigning them roles and placing them into groups.
                    - if your secret has been compromised - request a new one by rotating to a new access key ID
                    - rather than handing out your root account information to everyone that needs access, it is strongly recommended that you create separate users for each person needing access. Then give them access only to the services they need to access.
                    - Make sure to secure your own applications - AWS provides security groups which act as your firewalls to the associated instances - always make sure you lock this down and restrict access to the instances.
                    - Make sure to update all software packages and apply all security patches - all of the pre-cloud application security practices still apply in the cloud.
                - X509 Certificates

#####Designing for Failure
- Virual Servers (EC2) and Elastic IP
    - EC2 - this are the servers used in AWS
    - Elastic IPs 
        - are the static IP addresses designed for cloud computing
        - are created for the account and are not specific to a particular instance
        - after creating the elastic IP, you control it and choose when to release it
        - allows you to remap your public IP to any instance on your account
        - Example:
            - let's say you have this web application located at yourdomain.com, and your DNS server has this name associated with a specific IP address. What happens if this server dies? With a traditional static IP, your website will be down until, say you get a friendly data technician to replace the server or reconfigure a new server, or if you happen to have another server standing by, which will have a different IP address, you will need to change your DNS setting to point to this new IP and wait for the DNS to propagate before your site is back available. With Amazon EC2, and when using elastic IP's, you can easily handle this disaster differently. Since the elastic IP is not tied to a specific server but rather to your account, when disaster strikes, you can simply remap the association of the IP from the failed server to a new replacement server. No need to get any data technicians involved, and no need to make any DNS changes. So, design for failure, lesson number one.

- AWS Regions and Availability Zones 
    - The EC2s can be launched in one or more geographical regions. Each regions is a geographically independent collection of AWS resources. These regions are distributed world-wide within four primary land areas. There are four regions in North America:
        - US East - located in Virginia
        - US West - located in California
        - GovCloud - located in the northwest of the US:
            - designed to allow US government agencies, contractors, and their customers to move more sensitive into the cloud by addressing their specific regulatory and compliance requirements.
        - EU - located in Europe, Middle East, Africa area - located in Ireland
        - South America - located in Sao Paulo
        - Asia Pacific - Singapore, Sydney, Tokyo, and Beigin
<br><img src="img/3_aws_regions.png" width="400" hight="400">
    - These regions are independent of one-another and there is no data replicatins between them
    - Customers can launch instances in more than one region: if you have a very strict high-availability and distaster recover requirements that specify you must have redundant systems that are completely isolated and very far apart geographically, using more than one region will help you meet this requirement.
    - Any communications that you establish between regions is across the public internet, so encryption methods should be used to protect your sensitive data.
    - Availability Zones: 
        - Even within a region, you can achieve geographical isolation to meet your high availability and disaster recovery needs. This is because each region consists of multiple locations called availability zones.
        - Availability zones are distinct locations that are engineered to be insulated from failures from other availability zones, and provide inexpensive, low-latency network connectivity to other availability zones in the same region. Think of these as distinct data centers connected by fiber network. 
        - North America contains four regions and each of these containes multiple availability zones:
            - US East - 4 availability zones
            - US West (Oregon) - 3 availability zones
            - US West (California) - 2 availability zones
            - GovCloud - 2 availability zones
        - Each of these availability zones are connected by fiber network connection, and are locally geographically isolated from one another so a local disaster (fire, flood, tornado), or other physical breach occuring in one availability zone will not affect the other zones.
<br><img src="img/4_availability_zones.png" width="300" hight="300">

- Amazon Machine Image (AMI)
    - AMI is a packaged environment containing a software stack, along with all the necessary parts to properly set up and boot an EC2 instance. AMI is a unit of deployment, and you can launch as many instances from the AMI as you need.
    - There might be only a single AMI or several AMIs corresponding to different components in the system (web servers, app servers, database servers).
    - The AMI typically includes the following:
        - Template for root volume of the instance - an operating system, an applicaiton server and its applications.
        - Launch permissions - control which AWS accounts can use the AMI to launch instances
        - Block device mapping - specifies the volumes to attach to the instance when it's launched.
    - Amazon EC2 provides a number of tools to make creating AMIs easy, including the AWS management console.
	- After you've created an AMI with specific configurations, you can use that AMI to easily create new instance(s) as many times as needed, across multiple Availability Zones. You can do this programatically using the API, or by using the auto-scalling service, or using the console.
	- AWS Console:
	<br><img src="img/5_aws_console.png" width="500" hight="500">
	- A list of AMIs:
	<br><img src="img/6_amis.png" width="500" hight="500">
	- A list of Instances:
	<br><img src="img/7_instances.png" width="500" hight="500">
	- Create instance from AMI:
	<br><img src="img/9_create_instance_from _ami.png" width="500" hight="500">
	- Create an instance:
	<br><img src="img/8_create_instance.png" width="500" hight="500">

- Elastic Load Balancing (ELB): 
    - A component built to balance the traffic across EC2 instances and Availability Zones, and as such it allows your applications to achieve greater fault tolerance. It is elastic in that it automatically scales request-handling capability based on the traffic demands. Elasticity and redundancy is built into this service.
    - Characteristics of ELB:
    	- It can handle the routing and load balancing of your HTTP, HTTPS, and TCP traffic to your EC2 instance
	- It allows you to set up and configure health checks so it can know whether or not the instances to which it's routing traffic are healthy and should be used. 
        - It can automatically and dynamically grow and shrink with the demand patterns of your application
        - When creating a new ELB you get a single CNAME that you use for DNS configuration. For example, to use to point your web applications domains to.
	- The single CNAME does not change even as the ELB scaling is happening. So how does it do it? 

Fault Tolerance with ELB: 
- ELB helps you achieve fault tolerance by allowing you to distribute trafic across multiple EC2 instances and availability zones.
- Below we see a representation of an ELB routing traffic to two availability zones, but we know these two availability zones are actually geographically separate physical locations within a region. Our single CNAMEd ELB component actually resolves round robin DNS to ELB IP addresses in each availability zone and as traffic increases, AWS adds IP addresses to ELB's DNS entry and continues to round robin requests across the multiplying ELBs. Of course, as traffic decreases it removes the IP addresses from the ELB's DNS entry thereby reducing the number of load balancing components in the system. 
- In summary, use Elastic Load Balancer to easily distribute your system across multiple resources and abailability zones to ensure your system remains up and running even if a single resource fails or disaster strikes.
<br><img src="img/10_elastic_load_balancer_round_robin.png" width="300" hight="300">
