Name:           nanologger
Version:        1.0.0
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
make DESTDIR=%{buildroot} PREFIX=/usr install

%files
%license LICENSE
%doc README.md
/usr/lib/libnanologger.a
/usr/lib/libnanologger.so
/usr/include/nanologger.h
/usr/lib/pkgconfig/nanologger.pc

%changelog
* Wed Nov 06 2024 Israel López <israel.lopez.developer@gmail.com> - 1.0.0-1
- Versión inicial

