# Scalable Live Stream Ingest and Distribution System

## Overview

The Scalable Live Stream Ingest and Distribution System is a high-performance, distributed solution for handling live video streams at scale. It provides end-to-end functionality from stream ingestion to viewer distribution, with a focus on scalability, low latency, and reliability.

## Key Features

- RTMP ingest with load balancing
- Distributed transcoding and packaging system
- WebRTC distribution for ultra-low latency
- Geo-distributed edge network for content distribution
- Adaptive jitter buffer algorithms

## System Architecture

![System Architecture Diagram](./images/system_architecture.png)

For a detailed explanation of the system architecture, please see [architecture.md](./architecture.md).

## Getting Started

To set up the development environment and run the system, please refer to our [setup guide](./setup.md).

## Components

The system consists of several key components:

- [RTMP Ingest](./components/rtmp_ingest.md)
- [Load Balancer](./components/load_balancer.md)
- [Transcoding](./components/transcoding.md)
- [Packaging](./components/packaging.md)
- [WebRTC Distribution](./components/webrtc_distribution.md)
- [Edge Network](./components/edge_network.md)
- [Jitter Buffer](./components/jitter_buffer.md)

## API Documentation

- [Ingest API](./api/ingest_api.md)
- [Distribution API](./api/distribution_api.md)
- [Management API](./api/management_api.md)

