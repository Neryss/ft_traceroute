# ft_traceroute

A reproduction of the traceroute command.

## Implementation

Basis is pretty simple, send a bunch of UDP packets with an increasing value of TTL to the target (starting from 1, then 2, 3, 4...).
The target will return a TTL exceeded as ICMP packets until we have a TTL high enough to probe it, which will then return a non error packet.

We need a UDP send socket, and an ICMP retreive socket.
