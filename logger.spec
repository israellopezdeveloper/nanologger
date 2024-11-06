Name:           logger
Version:        1.0.0
Release:        1%{?dist}
Summary:        Una biblioteca de logging portátil para proyectos en C

License:        MIT
URL:            https://github.com/israellopezdeveloper/nanologger
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc, make

%description
Una descripción más detallada de tu biblioteca.

%prep
%setup -q

%build
make

%install
make DESTDIR=%{buildroot} install

%files
%license LICENSE
%doc README.md
/usr/lib/liblogger.a
/usr/lib/liblogger.so
/usr/include/logger.h
/usr/lib/pkgconfig/logger.pc

%changelog
* $(date +"%a %b %d %Y") Israel López <israel.lopez.developer@gmail.com> - 1.0.0-1
- Versión inicial

