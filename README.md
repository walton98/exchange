# Exchange

Simple exchange:

- Matching engine
- (soon to be) OMS
- UDP multicast communication with boost asio
- Lock-free SPSC ring-buffer work queue
- Nix-based dev environment

[![Exchange CI](https://github.com/walton98/exchange/actions/workflows/main.yml/badge.svg)](https://github.com/walton98/exchange/actions/workflows/main.yml)

## Development

To enter a dev shell with all the necessary build tools, use `nix develop`.

## Utilities

### Watcher

```bash
find -name '*.?pp' | entr -s "cmake --build build"
```

## Nix

### Cache

The CI automatically builds and pushes to the Cachix cache.
However, to push manually (e.g. when updating nixpkgs/clang):

```bash
nix build --json \
  | jq -r '.[].outputs | to_entries[].value' \
  | cachix push walton98
```

The cache is write-restricted and an authentication token is required
to push to it.

[Reference](https://docs.cachix.org/pushing)

## Architecture

### Components

The system is comprised of an accounts system and a matcher system.
Both of these components are sharded and have a load balancer to handle
the routing of messages. The load balancer is also responsible for
retransmission of missed messages, as well as ordering and storing the
input.

```mermaid
flowchart LR

LA1[Acct Load Balancer]

subgraph Accounts
    A1
    A2
    An
end

LA1 --> A1 & A2 & An

LM[Matcher Load Balancer]

subgraph Matcher
    M1
    M2
    Mn
end

A1 & A2 & An --> LM --> M1 & M2 & Mn

LA[Acct Load Balancer]

M1 & M2 & Mn --> LA
```

### Units

Each unit internally looks as follows:

```mermaid
flowchart

subgraph U[Unit]
    direction TB
    C[Consumer] --> QI[Input Queue]
    QI --> E[Engine]
    E --> S[Snapshotter]
    E --> QO[Output Queue]
    QO --> WAL
    QO --> P[Producer]
end
```

### Alternative Designs

It would be possible to have the account and matcher parts communicate
directly and for each one to be responsible for storing it's own queue
and broadcasting it to replicas and retransmitters. This sort of design
is discussed in [this talk](https://www.janestreet.com/tech-talks/building-an-exchange/).
