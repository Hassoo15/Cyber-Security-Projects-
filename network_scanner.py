#!/usr/bin/env python3
"""
Simple Network Scanner
Author: Hassan Tariq
Air University Cybersecurity Student
"""

import subprocess
import ipaddress

def scan_network(network="192.168.1.0/24"):
    """
    Scans a network range to find live hosts
    """
    print(f"[*] Scanning network: {network}")
    print("-" * 40)
    
    live_hosts = []
    
    # Scan each IP in the network
    for ip in ipaddress.IPv4Network(network):
        # Ping each host (1 packet, 1 second timeout)
        result = subprocess.call(
            ['ping', '-c', '1', '-W', '1', str(ip)],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL
        )
        
        if result == 0:
            live_hosts.append(str(ip))
            print(f"[+] Host {ip} is reachable")
    
    print("-" * 40)
    print(f"[*] Scan complete. Found {len(live_hosts)} live hosts.")
    return live_hosts

if __name__ == "__main__":
    # Example: Scan a small network
    scan_network("192.168.1.0/28")  # Only 16 IPs for testing
