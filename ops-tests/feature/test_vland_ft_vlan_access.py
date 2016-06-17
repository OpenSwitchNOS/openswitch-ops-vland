# -*- coding: utf-8 -*-
#
# Copyright (C) 2016 Hewlett Packard Enterprise Development LP
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

"""
OpenSwitch Test for functionality testing of vlan access mode.
"""

from __future__ import unicode_literals, absolute_import
from __future__ import print_function, division
from time import sleep


TOPOLOGY = """
# +-------+                   +-------+
# |       |     +-------+     |       |
# |  hs1  <----->  sw1  <----->  hs2  |
# |       |     +-------+     |       |
# +-------+                   +-------+

# Nodes
[type=openswitch name="Switch 1"] sw1
[type=host name="Host 1"] hs1
[type=host name="Host 2"] hs2

# Links
hs1:1 -- sw1:3
sw1:4 -- hs2:1
"""


def wait_until_interface_up(switch, portlbl, timeout=30, polling_frequency=1):
    """
    Wait until the interface, as mapped by the given portlbl, is marked as up.

    :param switch: The switch node.
    :param str portlbl: Port label that is mapped to the interfaces.
    :param int timeout: Number of seconds to wait.
    :param int polling_frequency: Frequency of the polling.
    :return: None if interface is brought-up. If not, an assertion is raised.
    """
    for i in range(timeout):
        status = switch.libs.vtysh.show_interface(portlbl)
        if status['interface_state'] == 'up':
            break
        sleep(polling_frequency)
    else:
        assert False, (
            'Interface {}:{} never brought-up after '
            'waiting for {} seconds'.format(
                switch.identifier, portlbl, timeout
            )
        )


def vlan_access_positive(sw1, hs1, hs2, step):
    """
    In this testcase reachability is tested when vlan access mode
    is configured on the interfaces of a switch.
    """
    dut_port1 = sw1.ports["3"]
    dut_port2 = sw1.ports["4"]

    step("Configure IP in host1")
    # Configure IP and bring UP host 1 interfaces
    hs1.libs.ip.interface('1', addr="2.2.2.2/24", up=True)

    step("Configure IP in host2")
    # Configure IP and bring UP host 2 interfaces
    hs2.libs.ip.interface('1', addr="2.2.2.3/24", up=True)

    step("Configure vlan 2 in switch")
    with sw1.libs.vtysh.ConfigVlan('2') as ctx:
        ctx.no_shutdown()

    step("Configure switch interfaces with vlan access configuration")
    # Configure IP and bring UP switch 1 interfaces
    with sw1.libs.vtysh.ConfigInterface(dut_port1) as ctx:
        ctx.no_routing()
        ctx.no_shutdown()
        ctx.vlan_access('2')

    with sw1.libs.vtysh.ConfigInterface(dut_port2) as ctx:
        ctx.no_routing()
        ctx.no_shutdown()
        ctx.vlan_access('2')

    # Wait until interfaces are up
    for switch, portlbl in [(sw1, dut_port1), (sw1, dut_port2)]:
        wait_until_interface_up(switch, portlbl)

    sleep(1)
    step("Ping should succeed as the switch's interfaces will allow untagged"
         " packets to pass between " + dut_port1 + " and " + dut_port2)
    ping = hs1.libs.ping.ping(1, '2.2.2.3')
    assert ping['transmitted'] == ping['received'] == 1, "Ping should have "\
        "worked when vlan access 2 is enabled on both the interfaces"


def vlan_access_negative(sw1, hs1, hs2, step):
    """
    In this testcase reachability is tested when two different vlans are
    configured as access for two interfaces
    """
    dut_port1 = sw1.ports["3"]
    dut_port2 = sw1.ports["4"]

    step("Configure vlan 3 in switch")
    # Configure and bring UP switch interfaces
    with sw1.libs.vtysh.ConfigVlan('3') as ctx:
        ctx.no_shutdown()

    step("Configure switch interfaces")
    with sw1.libs.vtysh.ConfigInterface(dut_port2) as ctx:
        ctx.no_vlan_access('2')
        ctx.vlan_access('3')

    # Wait until interfaces are up
    for switch, portlbl in [(sw1, dut_port1), (sw1, dut_port2)]:
        wait_until_interface_up(switch, portlbl)

    sleep(1)
    step("Ping should fail as different vlans are configured access for the"
         " two interfaces")
    ping = hs1.libs.ping.ping(1, '2.2.2.3')
    assert ping['loss_pc'] == 100, "ping should not happen as switch doesn't"\
        " vlan 2 access on " + dut_port2


def test_vlan_access(topology, step):
    """
    This testcase validates the basic functionality of vlan access mode
    configuration on switch.
    """
    sw1 = topology.get('sw1')
    hs1 = topology.get('hs1')
    hs2 = topology.get('hs2')

    assert sw1 is not None
    assert hs1 is not None
    assert hs2 is not None

    step("####### 1. Test case to validate vlan access positive scenario ###")
    vlan_access_positive(sw1, hs1, hs2, step)
    step("####### 2. Test case to validate vlan access negative scenario ###")
    vlan_access_negative(sw1, hs1, hs2, step)
