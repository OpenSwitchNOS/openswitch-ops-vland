# High level design of ops-vland
ops-vland is responsible for monitoring user VLAN configuration requests, determining the operational state of the VLANs (i.e., enabled, disabled), and set corresponding database fields to inform the switch driver and other daemons of the desired state for each VLAN.

## Reponsibilities
ops-vland
* monitor for entries in the port table being added, removed, or changed
* monitor for entries in the vlan table being added, removed, or changed
* for each vlan
  * if there is at least one valid member port and if the user has set the admin state to "enabled"
    * update hw_vlan_config to tell the switch driver to enable the vlan
    * and update status information

##  Design choices
ops-vland could have been incorporated into other daemons. It was considered best to keep VLAN configuration separate so enhancements would be straightforward.

## Relationships to external OpenSwitch entities
ops-vland operates exclusively on the OVS database. Other processes report the user intent (e.g., REST, CLI) and record that into the database. ops-vland will process this information and determine if the VLAN should be enabled or disabled, and then likewise update the database. Other daemons (such as switchd) monitor the fields that ops-vland writes and takes appropriate action.
```
  +--------------------+       +-----------+
  |      ops-vland     |       |           |
  |                    +------>+    OVSDB  |
  |                    |       |           |
  +--------------------+       +-----------+
```

## OVSDB-Schema
The following columns are READ by ops-vland:
```
  System:cur_cfg
  Port:name
  Port:vlan_mode
  Port:tag
  Port:trunks
  VLAN:name
  VLAN:id
  VLAN:admin
```

The following columns are WRITTEN by ops-vland:
```
  VLAN:hw_vlan_config
  VLAN:oper_state
  VLAN:oper_state_reason
```

## Internal structure
ops-vland is responsible for managing and reporting status for VLANs in OpenSwitch.  In traditional Open vSwitch, VLANs are configured implicitly via PORT table "tag" and "trunks" columns.  This leaves no way to explicitly configure or control individual VLAN behavior.

OpenSwitch added a new VLAN table to the OVSDB schema so that VLANs can be explicitly created by user configuration and extended to include per VLAN-specific features.

Each VLAN has administrative and operational states based on user configuration and other inputs.  A VLAN can be administratively enabled or disabled via "admin" column, allowing network administrators to quickly shutdown all traffic on a VLAN as needed.  VLANs are only configured in h/w when its operational state is "enabled".  Following is a summary of possible operational states of a VLAN:

```
  OPER_STATE  OPER_STATE_REASON  NOTES
  ----------  -----------------  -----

  disabled    admin_down         [admin] column is set to "down"
                                 by an administrator.

  disabled    no_member_port     VLAN has no member port, thus no
                                 traffic is flowing through it.

  enabled     ok                 VLAN is fine and is configured in h/w.
```


### Main loop
Main loop pseudo-code
```
  initialize OVS IDL
  initialize appctl interface
  while not exiting
     if db has been configured
        check for any changes in port table
        check for any changes in vlan table
        if any changes
           calculate new vlan states and update db
     check for appctl
     wait for IDL or appctl input
```

### Source modules
```
  +-----------------+        +----------------+
  |     vland.c     +------->+ appctl logic   |
  +-------+---------+        +----------------+
          |
          v
  +-----------------+        +----------------+
  |vland_ovsdb_if.c +------->|     OVSDB      |
  +-----------------+        +----------------+
```

### Data structures
#### port\_data
The port\_data structure contains the port name, vlan\_mode, and various status info. Each entry in the port table is represented by a port_data structure.

#### vlan\_data
The vlan\_data structure contains the vlan name, id, admin state, operational state, and operational state reason code. Each entry in the vlan table is represented by a vlan\_data structure.
