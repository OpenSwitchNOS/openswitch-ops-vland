# Feature Test Cases for vlan modes

## Contents
- [Verify the L2 reachability of vlan modes](#verify-the-l2-reachability-of-vla-modes)
- [Verify the L2 non-reachability of vlan modes](#verify-the-l2-non-reachability-of-vlan-modes)

### Objective
Verify the L2 reachability of vlan modes such as Access,Trunk,Native untag and Native tag

### Requirements
The requirements for this test case are:
 - OpenSwitch
 - Host1 and Host2

###Topology

# +-------+                   +-------+
# |       |     +-------+     |       |
# |  hs1  <----->  sw1  <----->  hs2  |
# |       |     +-------+     |       |
# +-------+                   +-------+


### Test setup
Connect OpenSwitch interface 1 to eth1 on the host1.
Connect OpenSwitch interface 2 to eth1 on the host2.

# Vlan Access port behaviour

#### Objective
Verify L2 rechability of vlan access mode

### Description
1. In host1 assign eth1 with Ip add 2.2.2.2/24 and make it up
2. In host2 assign eth1 with Ip add 2.2.2.3/24 and make it up
3. create vlan 2 and make it no shut
4. create two layer2 interface and make those  up
5. make those port as vlan2 access port
6. Ping 2.2.2.3 from the host1.

### Test result criteria
Ping result.

#### Test pass criteria
Ping succeeds.

#### Test fail criteria
Ping fails.

# Verify the negative rechability of vlan access port.

### Objective
Verify the negative-reachability of vlan access mode.

### Description
1.in host1 assign eth1 with Ip add 2.2.2.2/24 and make it up
2. In host2 assign eth1 with Ip add 2.2.2.3/24 and make it up
3. create vlan 2 ,vlan 3 and make them up
4. create two layer2 interface and make those up.
5. make  port1 as vlan2 access port and port2 as vlan 3 access port.
6. Ping 2.2.2.3 from the host1.

### Test result criteria
Ping result.

#### Test pass criteria
Ping fails.

#### Test fail criteria
Ping succeeds.

##  Verify the negative rechability of vlan access

### Objective
Verify the negative rechability of vlan access mode.

### Description
1. In host1 create eth1.1 with Ip add 2.2.2.2/24 and make it up
2. In host2 assign eth1 with Ip add 2.2.2.3/24 and make it up
3. create vlan 2 and  make it up
4. create two layer2 interface and make those up.
5. make  ports as vlan2 access port.
6. Ping 2.2.2.3 from the host1.

### Test result criteria
Ping result.

#### Test pass criteria
Ping fails.

#### Test fail criteria
Ping succeeds.

# Vlan trunk allowed port behaviour

### Objective
Verify the L2 reachability of vlan trunk port.

### Description
1. In host1 create eth1.1 with Ip add 2.2.2.2/24, assign vlan encapsulation 2 and make it up
2. In host1 create eth1.2 with Ip add 3.3.3.3/24, assign vlan encapsulation 2 and make it up
3. In host2 create eth1.1 with Ip add 2.2.2.3/24, assign vlan encapsulation 3 and make it up
4. In host2 create eth1.2 with Ip add 3.3.3.4/24, assign vlan encapsulation 3 and make it up
5. Create vlan 2,3 and  make tem up
6. Create two layer2 interface and make those up.
7. Make  port1 as vlan2 trunk port and port2 as vlan3 trunk port .
8. Ping 2.2.2.3 from the host1.
9. Ping 3.3.3.4 from the host1

### Test result criteria
Ping result.

#### Test pass criteria
Ping successed.

#### Test fail criteria
Ping fails.

# Verify the negative rechability of vlan trunk allowed

### Objective
Verify the negative-reachability of vlan trunk allowed port.

### Description
1. In host1 create eth1 with Ip add 2.2.2.2/24 and make it up
2. In host2 create eth1.2 with Ip add 2.2.2.3/24, assign vlan encapsulation 2 and make it up
3. Create vlan 2 and  make tem up
4. Create two layer2 interface and make those up.
5. Make  port1 as vlan2 trunk port.
6. Ping 2.2.2.3 from the host1.

### Test result criteria
Ping result.

#### Test pass criteria
Ping fails.

#### Test fail criteria
Ping succeeds.

## Verify the negative rechability-2 of vlan trunk allowed

### Objective
Verify the negative-reachability of vlan trunk allowed port.
### Description
1. In host1 create eth1.2 with Ip add 2.2.2.2/24 ,assign vlan encasulation 3 and make it up.
2. In host2 create eth1.2 with Ip add 2.2.2.3/24, assign vlan encapsulation 2 and make it up.
3. Create vlan 2 and  make them up.
4. Create two layer2 interface and make those up.
5. Make  port1 as vlan2 trunk port.
6. Ping 2.2.2.3 from the host1.

### Test result criteria
Ping result.

#### Test pass criteria
Ping fails.

#### Test fail criteria
Ping succeeds.

# Vlan trunk native port behaviour

#### Objective
Verify the L2 reachability of vlan trunk native port.
### Description
1. In host1 create eth1.2 with Ip add 2.2.2.2/24, assign vlan encasulation 2 and make it up.
2. In host2 assign eth1 with Ip add 2.2.2.3/24 and make it up.
3. create vlan 2 and make it no shut.
4. create two layer2 interface and make those  up.
5. make port 1 as "vlan trunk allowed 2" and port 2 as "vlan trunk native 2".
6. Ping 2.2.2.3 from the host1.

### Test result criteria
Ping result.

#### Test pass criteria
Ping succeeds.

#### Test fail criteria
Ping fails.

##  Verify the negative rechability of vlan trunk native.

### Objective
Verify the negative-reachability of vlan trunk native port.
### Description
1. In host1 create eth1.2 with Ip add 2.2.2.2/24 ,assign vlan encapsulation 3 and make it up.
2. In host2 create eth1.2 with Ip add 2.2.2.3/24, assign vlan encapsulation 2 and make it up.
3. Create vlan 2 and  make tem up.
4. Create two layer2 interface and make those up.
5. make port 1 as "vlan trunk allowed 2" and port 2 as "vlan trunk native 2".
6. Ping 2.2.2.3 from the host1.

### Test result criteria
Ping result.

#### Test pass criteria
Ping fails.

#### Test fail criteria
Ping succeeds.

# Vlann trunk netive tag port behaviour

#### Objective
Verify the negative-reachability of vlan trunk native tag port.

### Description
1. In host1 assign eth1 with Ip add 2.2.2.2/24 and make it up.
2. In host2 create eth1.2 with Ip add 2.2.2.3/24 ,assign vlan encasulation 2 and make it up.
3. create vlan 2 and make it up.
4. create two layer2 interface and make those  up.
5. make port 1 as "vlan trunk native 2" and port 2 as "vlan trunkallowed 2" and vlan "trunk native tag".
6. Ping 2.2.2.3 from the host1.

### Test result criteria
Ping result.

#### Test pass criteria
Ping succeeds.

#### Test fail criteria
Ping fails.

##  Verify the negative rechability of vlan trunk native tag

### Objective
Verify the negative-reachability of vlan trunk native tag mode.
### Description
1. In host1 assign eth1 with Ip add 2.2.2.2/24 and make it up.
2. In host2 create eth1 with Ip add 2.2.2.3/24 and make it up.
3. Create vlan 2 and  make them up.
4. Create two layer2 interface and make those up.
5. make port 1 as "vlan trunk native 2" and port 2 as "vlan trunkallowed 2" and vlan "trunk native tag".
6. Ping 2.2.2.3 from the host1.

### Test result criteria
Ping result.

#### Test pass criteria
Ping fails.

#### Test fail criteria
Ping succeeds.
