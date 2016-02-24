/*
 * Copyright (C) 1997, 1998, 1999, 2000, 2001, 2002 Kunihiro Ishiguro
 * Copyright (C) 2015-2016 Hewlett Packard Enterprise Development LP
 *
 * GNU Zebra is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */
/****************************************************************************
 * @ingroup cli
 *
 * @file vtysh_ovsdb_vlan_context.c
 * Source for registering client callback with vlan context.
 *
 ***************************************************************************/

#include "vtysh/zebra.h"
#include "vtysh/vty.h"
#include "vtysh/vector.h"
#include "vswitch-idl.h"
#include "openswitch-idl.h"
#include "vtysh/vtysh_ovsdb_if.h"
#include "vtysh/vtysh_ovsdb_config.h"
#include "vtysh/utils/vlan_vtysh_utils.h"
#include "vtysh_ovsdb_vlan_context.h"
#include "vlan_vty.h"

char vlancontextclientname[] = "vtysh_vlan_context_clientcallback";
/*-----------------------------------------------------------------------------
| Function : vtysh_vlan_context_clientcallback
| Responsibility : client callback routine
| Parameters :
|     void *p_private: void type object typecast to required
| Return : void
-----------------------------------------------------------------------------*/

vtysh_ret_val
vtysh_vlan_context_clientcallback(void *p_private)
{
  vtysh_ovsdb_cbmsg_ptr p_msg = (vtysh_ovsdb_cbmsg *)p_private;
  const struct ovsrec_vlan *vlan_row;
  struct shash sorted_vlan_id;
  const struct shash_node **nodes;
  int idx=0;
  int count=0;
  char str[15];

  vlan_row = ovsrec_vlan_first(p_msg->idl);
  if (vlan_row == NULL)
  {
      return e_vtysh_ok;
  }

  shash_init(&sorted_vlan_id);

  OVSREC_VLAN_FOR_EACH(vlan_row, p_msg->idl)
  {
      sprintf(str, "%ld", vlan_row->id);
      shash_add(&sorted_vlan_id, str, (void *)vlan_row);
  }

  nodes = sort_vlan_id(&sorted_vlan_id);
  count = shash_count(&sorted_vlan_id);

  for (idx = 0; idx < count; idx++)
  {
      vlan_row = (const struct ovsrec_vlan *)nodes[idx]->data;
      if (!check_if_internal_vlan(vlan_row))
      {
          vtysh_ovsdb_cli_print(p_msg, "%s %d", "vlan", vlan_row->id);

          if (strcmp(vlan_row->admin, OVSREC_VLAN_ADMIN_UP) == 0)
          {
              vtysh_ovsdb_cli_print(p_msg, "%4s%s", "", "no shutdown");
          }

          if (vlan_row->description != NULL)
          {
              vtysh_ovsdb_cli_print(p_msg, "%4s%s%s", "", "description ",
                                                     vlan_row->description);
          }
       }
  }
  shash_destroy(&sorted_vlan_id);
  free(nodes);

  return e_vtysh_ok;
}

/*-----------------------------------------------------------------------------
| Function : vtysh_ovsdb_intftable_parse_vlan
| Responsibility : Used for VLAN related config
| Parameters :
|     const char *if_name           : Name of interface
|     vtysh_ovsdb_cbmsg_ptr p_msg   : Used for idl operations
| Return : vtysh_ret_val
-----------------------------------------------------------------------------*/
static vtysh_ret_val
vtysh_ovsdb_intftable_parse_vlan(const char *if_name,
                                 vtysh_ovsdb_cbmsg_ptr p_msg)
{
  const struct ovsrec_port *port_row;
  int i;

  port_row = port_lookup(if_name, p_msg->idl);
  if (port_row == NULL)
  {
    return e_vtysh_ok;
  }
  if (port_row->vlan_mode == NULL)
  {
    return e_vtysh_ok;
  }
  else if (strcmp(port_row->vlan_mode, OVSREC_PORT_VLAN_MODE_ACCESS) == 0)
  {
    if(port_row->n_tag == 1)
    {
      vtysh_ovsdb_cli_print(p_msg, "%4s%s%d", "", "vlan access ",
                            *port_row->tag);
    }
  }
  else if (strcmp(port_row->vlan_mode, OVSREC_PORT_VLAN_MODE_TRUNK) == 0)
  {
    for (i = 0; i < port_row->n_trunks; i++)
    {
      vtysh_ovsdb_cli_print(p_msg, "%4s%s%d", "", "vlan trunk allowed ",
                            port_row->trunks[i]);
    }
  }
  else if (strcmp(port_row->vlan_mode, OVSREC_PORT_VLAN_MODE_NATIVE_UNTAGGED)
           == 0)
  {
    if (port_row->n_tag == 1)
    {
      vtysh_ovsdb_cli_print(p_msg, "%4s%s%d", "", "vlan trunk native ",
                            *port_row->tag);
    }
    for (i = 0; i < port_row->n_trunks; i++)
    {
      vtysh_ovsdb_cli_print(p_msg, "%4s%s%d", "", "vlan trunk allowed ",
                            port_row->trunks[i]);
    }
  }
  else if (strcmp(port_row->vlan_mode, OVSREC_PORT_VLAN_MODE_NATIVE_TAGGED)
           == 0)
  {
    if (port_row->n_tag == 1)
    {
      vtysh_ovsdb_cli_print(p_msg, "%4s%s%d", "", "vlan trunk native ",
                            *port_row->tag);
    }
    vtysh_ovsdb_cli_print(p_msg, "%4s%s", "", "vlan trunk native tag");
    for (i = 0; i < port_row->n_trunks; i++)
    {
      vtysh_ovsdb_cli_print(p_msg, "%4s%s%d", "", "vlan trunk allowed ",
                            port_row->trunks[i]);
    }
  }

  return e_vtysh_ok;
}

/*-----------------------------------------------------------------------------
| Function : vtysh_intf_context_vlan_clientcallback
| Responsibility : Verify if interface is VLAN and parse vlan related config
| Parameters :
|     const char *if_name           : Name of interface
|     vtysh_ovsdb_cbmsg_ptr p_msg   : Used for idl operations
|     bool interfaceNameWritten     : Check if "interface x" has already been
|                                     written
| Return : vtysh_ret_val
-----------------------------------------------------------------------------*/
vtysh_ret_val
vtysh_intf_context_vlan_clientcallback(void *p_private)
{
  const struct ovsrec_port *port_row;
  vtysh_ovsdb_cbmsg_ptr p_msg = (vtysh_ovsdb_cbmsg *)p_private;
  const struct ovsrec_interface *ifrow = NULL;

  ifrow = (struct ovsrec_interface *)p_msg->feature_row;
  port_row = port_lookup(ifrow->name, p_msg->idl);
  if (!port_row) {
    return e_vtysh_ok;
  }
  if (!check_iface_in_vrf(ifrow->name)) {
    if (!p_msg->disp_header_cfg) {
      vtysh_ovsdb_cli_print(p_msg, "interface %s", ifrow->name);
    }
    vtysh_ovsdb_cli_print(p_msg, "%4s%s", "", "no routing");
    vtysh_ovsdb_intftable_parse_vlan(ifrow->name, p_msg);
  }
  return e_vtysh_ok;
}

/*-----------------------------------------------------------------------------
| Function : vtysh_init_vlan_contextclients
| Responsibility : Registers the client callback routines for vlancontext
| Parameters :
| Return :
-----------------------------------------------------------------------------*/
int
vtysh_init_vlan_context_clients()
{
  vtysh_context_client client;
  vtysh_ret_val retval = e_vtysh_error;

  client.p_client_name = vlancontextclientname;
  client.client_id = e_vtysh_vlan_context_config;
  client.p_callback = &vtysh_vlan_context_clientcallback;
  retval = vtysh_context_addclient(e_vtysh_vlan_context, e_vtysh_vlan_context_config, &client);
  if(e_vtysh_ok != retval)
  {
    vtysh_ovsdb_config_logmsg(VTYSH_OVSDB_CONFIG_ERR,
                              "vlan context unable to add config callback");
    assert(0);
    return retval;
  }
  return e_vtysh_ok;
}
