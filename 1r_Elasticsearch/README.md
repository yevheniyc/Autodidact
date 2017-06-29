## Elastisearch - The Definitive Guide

NOTE: Some parts of the group are copied for learning purposes

Elasticsearch is a distributed, scalable, real-time search and analytics engine. It enables you to search, analyze, and explore your data, often in ways that you did not anticipate at the start of a project. It exists because raw data sitting on a hard drive is just not useful.

Whether you need full-text search, real-time analytics of structured data, or a combination of the two, this book introduces you to the fundamental concepts required to start working with Elastic search at a basic level. With these foundations laid, it will move on to more-advanced search techniques, which you will need to shape the search experience to fit your requirements. 

Elasticsearch is not just about full-text search. We explain structured search, analytics, the complexities of dealing with human language, geolocation, and relationships. We will also discuss how best to model your data to take advantage of the horizontal scalability of Elasticseach, and how to configure and monitor your cluster when moving to production.

Elasticsearch is a real-time distributed search and analytics engine. It allows you to explore your data at a speed and at a scale never before possible. It is used for full-text search, structured search, analytics, and all three in combination:
- Wikipedia uses Elasticsearch to provide full-text search with highlighted search snippets, and search-as-you-type and did-you-ean suggestions
- The Guardian uses Elasticsearch to combine visitor logs with social-network data to provide real-time feedback to its editors about the public's repsonse to new articles.
- Stack Overflow combines full-text search with geolocation querries and uses more-like-this to find related questions and answers.
- GitHub uses Elasticsearch to query 130 billion lines of code

But Elasticsearch is not just for mega-corporations. It has enabled many startups like Datadoc and Klout to prototype ideas and to turn them into scalable solutions. Elasticsearch can run on your laptop, or scal out to hundreds of servers and petabytes of data.

No individual part of Elasticsearch is new or revolutionary. Full-text search has been done before, as have analytics systems and distributed databases. The revolution is the combination of these individually useful parts into a single, coherent, real-time application. It has a low barrier to entry for the new user, but can keep pace with you as your skills and needs grow.

Unfortunately, most databases are astonishingly inept at extracting actionable knowledge from your data. Sure, they can filter by timestamp or exact values, but can they perform full-text search, handle synonyms, and score documents by relevance? Can thy generate anlytics and aggregations from the same data? Most important, can they do this in real time without big batch-processing jobs?

This is what sets Elasticsearch apart: Elasticsearch encourages you to exmplore and utilize your data, rather than letting it rot in a warehouse because it is too difficult to query.

Elasticsearch is an open-source search engine built on top of Apache Lucene, a full-text search-engine library. Lucene is arguable the most advanced, high-performance, and fully featured search engine library in existence today - both open source and proprietary.

But Lucene is just a library. To leverage its power, you need to work in Java and to integrate Lucene directly with your application. Worse, you will likely require a degree in information retrieval to understand how it works. Lucene is very complex.

Elasticsearch is also written in Java and uses Lucene internally for all its indexing and searching, but it aims to make full-text search easy by hinding the complexities of Lucene behind a simple, coherent, RESTful API.

However, Elasticsearch is much more than just Lucene and much more than "just" full-text search. It can also be described as follows:
- A distributed real-time document store where every field is indexed and searchable
- A distributed search engine with real-time analytics
- Capable of scaling to hundreds of servers and petabytes of structured and unstructured data

And it packages up all this functionality into a standalone server that your application can talk to via a simple RESTful API, using a web client from your favorite programming language, or even from the command line.

It is easy to get started with Elasticsearch. It ships with sensible defaults and hides complicated search theory away from beginners. It just works, right out of the box. With minimal understanding you can soon become productive. 
