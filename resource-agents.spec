Name:                resource-agents
Summary:             Open Source HA Reusable Cluster Resource Scripts
Version:             4.15.1
Release:             1
License:             GPLv2+ and LGPLv2+
URL:                 https://github.com/ClusterLabs/resource-agents
Source0:             https://github.com/ClusterLabs/resource-agents/archive/resource-agents-%{version}.tar.gz
Obsoletes:           heartbeat-resources <= %{version}
Provides:            heartbeat-resources = %{version}
BuildRequires:       automake autoconf pkgconfig gcc perl-interpreter perl-generators python3-devel
BuildRequires:       libxslt glib2-devel which docbook-style-xsl docbook-dtds
BuildRequires:       libqb-devel
Requires:            bash grep sed gawk procps-ng hostname net-tools psmisc util-linux
Requires:            e2fsprogs xfsprogs nfs-utils cifs-utils iproute lvm2
%description
Resource agent is a standardized interface for a cluster resource. In translates a standard set of operations into
steps specific to the resource or application, and interprets their results as success or failure.

%package -n ldirectord
License:             GPLv2+
Summary:             Monitoring Daemon for Maintaining High Availability Resources
Obsoletes:           heartbeat-ldirectord <= %{version}
Provides:            heartbeat-ldirectord = %{version}
BuildRequires:       perl-podlators
Requires:            perl-Net-SSLeay perl-libwww-perl perl-MailTools ipvsadm logrotate
BuildRequires:       systemd
%{?systemd_requires}
%description -n ldirectord
Ldirectord is a daemon to monitor and administer real servers in a cluster of load
balanced virtual servers.Currently, HTTP, HTTPS, and FTP services are supported.
ldirectord typically is started from heartbeat but can also be run from the command line.

%package     help
Summary:             Help documentation for resource-agents
%description help
Help documentation for resource-agents.

%prep
%autosetup -n %{name}-%{version} -p1

%build
if [ ! -f configure ]; then
  ./autogen.sh
fi
export CFLAGS="$(echo '%{optflags}')"
%global conf_opt_fatal "--enable-fatal-warnings=no"
%configure \
    %{conf_opt_fatal} --with-systemdsystemunitdir=%{_unitdir} --with-systemdtmpfilesdir=%{_tmpfilesdir} \
    --with-pkg-name=%{name} --with-ras-set=linux-ha
%make_build

%install
%make_install

%files
%doc AUTHORS COPYING COPYING.GPLv3 COPYING.LGPL
%doc doc/README.webapps
%dir %{_usr}/lib/ocf
%dir %{_usr}/lib/ocf/resource.d
%dir %{_usr}/lib/ocf/lib
%{_usr}/lib/ocf/lib/heartbeat
%{_usr}/lib/ocf/resource.d/heartbeat
%{_unitdir}/resource-agents-deps.target
%dir %{_datadir}/%{name}
%dir %{_datadir}/%{name}/ocft
%{_tmpfilesdir}/%{name}.conf
%{_datadir}/%{name}/ocft/{configs,caselib,README,README.zh_CN,helpers.sh}
%{_datadir}/pkgconfig/%{name}.pc
%exclude %{_datadir}/%{name}/ocft/{runocft,runocft.prereq}
%{_sbindir}/ocf-tester
%{_sbindir}/ocft
%{_includedir}/heartbeat
%dir %attr (1755, root, root)  %{_var}/run/resource-agents
%dir %{_sysconfdir}/ha.d
%{_sysconfdir}/ha.d/shellfuncs
%{_libexecdir}/heartbeat

%preun -n ldirectord
%systemd_preun ldirectord.service

%postun -n ldirectord
/sbin/ldconfig
%systemd_postun_with_restart ldirectord.service

%post -n ldirectord
%systemd_post ldirectord.service

%files -n ldirectord
%{_sbindir}/ldirectord
%doc COPYING ldirectord/ldirectord.cf
%config(noreplace) %{_sysconfdir}/logrotate.d/ldirectord
%dir %{_sysconfdir}/ha.d
%dir %{_sysconfdir}/ha.d/resource.d
%{_sysconfdir}/ha.d/resource.d/ldirectord
%{_unitdir}/ldirectord.service
%exclude %{_sysconfdir}/init.d/ldirectord

%files help
%doc heartbeat/README.galera ChangeLog
%doc %{_datadir}/%{name}/{ra-api-1.dtd,metadata.rng}
%{_mandir}/man7/*.7*
%{_mandir}/man8/{ocf-tester.8*,ldirectord.8*}

%changelog
