# Resource agents

This repository contains resource agents (RAs) compliant
with the Open Cluster Framework (OCF) specification.

These resource agents are used by two cluster resource
management implementations:

- Pacemaker
- rgmanager

More information about OCF resource agents is available
in the OCF Resource Agent Developer's guide (link below).


## rpm
- Run these commands to generate the .spec-file you need from the .in-file:
```bash
./autogen.sh
./configure
make rpm
```
And then follow these instructions for building RPM.

## Where can I find more information?

* [ClusterLabs website](http://www.clusterlabs.org/)
* [OCF Resource Agent Developer's guide](https://github.com/ClusterLabs/resource-agents/blob/master/doc/dev-guides/ra-dev-guide.asc)
* Mailing lists for [users](http://oss.clusterlabs.org/mailman/listinfo/users) and [developers](http://oss.clusterlabs.org/mailman/listinfo/developers)
* #clusterlabs IRC channel on [freenode](http://freenode.net/)

