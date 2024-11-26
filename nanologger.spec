Name:           nanologger
Version:        1.0.2
Release:        1%{?dist}
Summary:        A portable logging library for C projects.

License:        MIT
URL:            https://github.com/israellopezdeveloper/nanologger
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc, make

%description
A portable logging library for C projects.

%prep
%setup -q

%build
make

%install
mkdir -p %{buildroot}/usr/lib
mkdir -p %{buildroot}/usr/include
mkdir -p %{buildroot}/usr/lib/pkgconfig
mkdir -p %{buildroot}/usr/share/man/man3
cp -r man/ %{buildroot}/usr/share/
make DESTDIR=%{buildroot} PREFIX=/usr install

%files
%license LICENSE
%doc README.md
/usr/lib/libnanologger.a
/usr/lib/libnanologger.so
/usr/include/nanologger.h
/usr/lib/pkgconfig/nanologger.pc
/usr/share/man/man3/*.3.gz
/usr/share/man/man3.es/*.3.gz
/usr/share/man/man3.zh/*.3.gz

%define debug_package %{nil}


%changelog
* Wed Nov 06 2024 Israel López <israel.lopez.developer@gmail.com> - 1.0.0-1
- Versión inicial

