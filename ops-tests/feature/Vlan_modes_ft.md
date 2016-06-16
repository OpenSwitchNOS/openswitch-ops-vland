# Feature Test Cases for vlan modes

The following test cases verify vlan modes configuration is :
<!-- TOC depth:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [Feature Test Cases for vlan modes](#feature-test-cases-for-vlan-modes)
	- [Objective](#objective)
	- [Requirements](#requirements)
	- [Setup](#setup)
		- [Topology](#topology)
		- [Test setup](#test-setup)
	- [Vlan Access port behavior](#vlan-access-port-behavior)
		- [Verifying vlan access mode](#Verifying-vlan-access-mode)
		- [Verify the negative reachability-1 of vlan access port](#verify-the-negative-reachability-1-of-vlan-access-port)
		- [Verify the negative reachability-2 of vlan access](#verify-the-negative-reachability-2-of-vlan-access)
	- [Vlan trunk allowed port behavior](#vlan-trunk-allowed-port-behavior)
		- [Verify l2 vlan trunk port mode](#verify-l2-vlan-trunk-port-mode)
		- [Verify the negative reachability-1 of vlan trunk allowed](#verify-the-negative-reachability-1-of-vlan-trunk-allowed)
		- [Verify the negative reachability-2 of vlan trunk allowed](#verify-the-negative-reachability-2-of-vlan-trunk-allowed)
	- [Vlan trunk native port behavior](#vlan-trunk-native-port-behavior)
		- [Verify the L2 vlan trunk native untag mode](#verify-the-l2-vlan-trunk-native-untag-mode)
		- [Verify the negative reachability of vlan trunk native.](#verify-the-negative-reachability-of-vlan-trunk-native)
	- [Vlan trunk native tag port behavior](#vlan-trunk-native-tag-port-behavior)
		- [Verify L2 vlan trunk native tag  mode](#verify-l2-vlan-trunk-native-tag-mode)
		- [Verify the negative reachability of vlan trunk native tag](#verify-the-negative-reachability-of-vlan-trunk-native-tag)
<!-- /TOC -->


## Objective
Verify the L2 reachability of vlan modes such as Access,Trunk,Native untag and Native tag.

## Requirements
The requirements for this test case are:
 - OpenSwitch
 - Host1 and Host2

## Setup
### Topology

```
 +-------+                   +-------+
 |       |     +-------+     |       |
 |  hs1  <----->  sw1  <----->  hs2  |
 |       |     +-------+     |       |
 +-------+                   +-------+
```

### Test setup
Connect OpenSwitch interface 1 to eth1 on the host1.
Connect OpenSwitch interface 2 to eth1 on the host2.

## Vlan Access port behavior
### Verifying vlan access mode
#### Objective
Verify L2 reachability of vlan access mode.

#### Description
1. In host1 assign eth1 with IP add 2.2.2.2/24 and make it up
2. In host2 assign eth1 with IP add 2.2.2.3/24 and make it up
3. Create vlan 2 and make it no shut
4. Create two layer2 interface and make those  up
5. Make those port as vlan2 access port
6. Ping 2.2.2.3 from the host1.

#### Test result criteria
Ping result.

##### Test pass criteria
Ping succeeds.

##### Test fail criteria
Ping fails.

### Verify the negative reachability-1 of vlan access port

#### Objective
Verify the negative-reachability of vlan access mode.

#### Description
1.in host1 assign eth1 with IP add 2.2.2.2/24 and make it up
2. In host2 assign eth1 with IP add 2.2.2.3/24 and make it up
3. create vlan 2 ,vlan 3 and make them up
4. create two layer2 interface and make those up.
5. make  port1 as vlan2 access port and port2 as vlan 3 access port.
6. Ping 2.2.2.3 from the host1.

#### Test result criteria
Ping result.

##### Test pass criteria
Ping fails.

##### Test fail criteria
Ping succeeds.

### Verify the negative reachability-2 of vlan access

#### Objective
Verify the negative reachability of vlan access mode.

#### Description
1. In host1 create eth1.1 with IP add 2.2.2.2/24,assign vlan encapsulation 2 and make it up.
2. In host2 assign eth1.2 with IP add 2.2.2.3/24, assign vlan encapsulation 2 and make it up.
3. Create vlan 2 and  make it up.
4. Create two layer2 interface and make those up.
5. Make  ports as vlan2 access port.
6. Ping 2.2.2.3 from the host1.

#### Test result criteria
Ping result.

##### Test pass criteria
Ping fails.

##### Test fail criteria
Ping succeeds.

## Vlan trunk allowed port behavior

### Verify l2 vlan trunk port mode
#### Objective
Verify the L2 reachability of vlan trunk port.

#### Description
1. In host1 create eth1.2 with IP add 2.2.2.2/24, assign vlan encapsulation 2 and make it up
2. In host1 create eth1.3 with IP add 3.3.3.3/24, assign vlan encapsulation 3 and make it up
3. In host2 create eth1.2 with IP add 2.2.2.3/24, assign vlan encapsulation 2 and make it up
4. In host2 create eth1.3 with IP add 3.3.3.4/24, assign vlan encapsulation 3 and make it up
5. Create vlan 2,3 and  make tem up
6. Create two layer2 interface and make those up.
7. Make  port1 and port 2 as vlan trunk allowed 2 and 3 .
8. Ping 2.2.2.3 from the host1.
9. Ping 3.3.3.4 from the host1

#### Test result criteria
Ping result.

##### Test pass criteria
Ping succeeds.

##### Test fail criteria
Ping fails.

### Verify the negative reachability-1 of vlan trunk allowed

#### Objective
Verify the negative-reachability of vlan trunk allowed port.

#### Description
1. In host1 create eth1 with IP add 2.2.2.2/24 and make it up
2. In host2 create eth1.2 with IP add 2.2.2.3/24, assign vlan encapsulation 2 and make it up
3. Create vlan 2,3 and  make tem up
4. Create two layer2 interface and make those up.
5. Make  port1 as vlan2 trunk port.
6. Make port2 as vlan trunk allowed 2 and 3.
7. Ping 2.2.2.3 from the host1.

#### Test result criteria
Ping result.

##### Test pass criteria
Ping fails.

##### Test fail criteria
Ping succeeds.

### Verify the negative reachability-2 of vlan trunk allowed

#### Objective
Verify the negative-reachability of vlan trunk allowed port.
#### Description
1. In host1 create eth1.2 with IP add 2.2.2.2/24 ,assign vlan encapsulation 2 and make it up.
2. In host2 create eth1.3 with IP add 2.2.2.3/24, assign vlan encapsulation 3 and make it up.
3. Create vlan 2,3 and  make them up.
4. Create two layer2 interface and make those up.
5. Make  port1 as vlan2 trunk port.
6. Make  port2 as vlan3 trunk port.
6. Ping 2.2.2.3 from the host1.

#### Test result criteria
Ping result.

##### Test pass criteria
Ping fails.

##### Test fail criteria
Ping succeeds.

## Vlan trunk native port behavior

### Verify the L2 vlan trunk native untag mode

#### Objective
Verify the L2 reachability of vlan trunk native port.
#### Description
1. In host1 create eth1.2 with Ip add 2.2.2.2/24, assign vlan encapsulationasulation 2 and make it up.
2. In host2 assign eth1 with IP add 2.2.2.3/24 and make it up.
3. create vlan 2 and make it no shut.
4. create two layer2 interface and make those  up.
5. make port 1 as "vlan trunk allowed 2" and port 2 as "vlan trunk native 2".
6. Ping 2.2.2.3 from the host1.

#### Test result criteria
Ping result.

##### Test pass criteria
Ping succeeds.

##### Test fail criteria
Ping fails.

### Verify the negative reachability of vlan trunk native.

#### Objective
Verify the negative-reachability of vlan trunk native port.
#### Description
1. In host1 create eth1.2 with IP add 2.2.2.2/24 ,assign vlan encapsulation 3 and make it up.
2. In host2 create eth1.2 with IP add 2.2.2.3/24, assign vlan encapsulation 2 and make it up.
3. Create vlan 2 and  make them up.
4. Create two layer2 interface and make those up.
5. make port 1 as "vlan trunk allowed 2" and port 2 as "vlan trunk native 2".
6. Ping 2.2.2.3 from the host1.

#### Test result criteria
Ping result.

##### Test pass criteria
Ping fails.

##### Test fail criteria
Ping succeeds.

## Vlan trunk native tag port behavior

### Verify L2 vlan trunk native tag  mode
#### Objective
Verify the negative-reachability of vlan trunk native tag port.
#### Description
1. In host1 assign eth1 with IP add 2.2.2.2/24 and make it up.
2. In host2 create eth1.2 with IP add 2.2.2.3/24 ,assign vlan encapsulation 2 and make it up.
3. create vlan 2 and make it up.
4. create two layer2 interface and make those  up.
5. make port 1 as "vlan trunk native 2" and port 2 as "vlan trunk allowed 2" and vlan "trunk native tag".
6. Ping 2.2.2.3 from the host1.

#### Test result criteria
Ping result.

##### Test pass criteria
Ping succeeds.

##### Test fail criteria
Ping fails.

### Verify the negative reachability of vlan trunk native tag

#### Objective
Verify the negative-reachability of vlan trunk native tag mode.
#### Description
1. In host1 assign eth1 with IP add 2.2.2.2/24 and make it up.
2. In host2 create eth1 with IP add 2.2.2.3/24 and make it up.
3. Create vlan 2 and  make them up.
4. Create two layer2 interface and make those up.
5. make port 1 as "vlan trunk native 2" and port 2 as "vlan trunk allowed 2" and vlan "trunk native tag".
6. Ping 2.2.2.3 from the host1.

#### Test result criteria
Ping result.

##### Test pass criteria
Ping fails.

##### Test fail criteria
Ping succeeds.
