local L = {}

L.lexer = "perl"

L.singleLineComment = "# "

L.first_line = {
	"^#!.*perl"
}

L.extensions = {
	"pl",
	"pm",
	"plx",
}

L.keywords = {
	[0] = "ARGV AUTOLOAD Accept BEGIN Balloon Button CHECK CORE DATA DESTROY END Entry Frame INIT Label MainLoop Radiobutton STDERR STDIN STDOUT SUPER Tr UNITCHECK UNIVERSAL __DATA__ __END__ __FILE__ __LINE__ __PACKAGE__ __SUB__ abs accept address alarm and atan2 attach auth_type autoEscape bind binmode bless br break button caller caption chdir checkbox checkbox_group chmod chomp chop chown chr chroot close closedir cmp compile configure connect constant continue cookie cos crypt dbmclose dbmopen default defaults defined deiconify delete delete_all die div do dump each else elsif em end end_h1 end_html end_table end_ul endform endgrent endhostent endif endnetent endprotoent endpwent endservent eof eq escape escape_HTML eval evalbytes exec exists exit exp fc fcntl filefield fileno flock font for foreach fork format formline ge geometry getc getgrent getgrgid getgrnam getgrname gethostbyaddr gethostbyname gethostent getlogin getnetbyaddr getnetbyname getnetent getpeername getpgrp getppid getpriority getprotobyname getprotobynumber getprotoent getpwent getpwnam getpwuid getservbyname getservbyport getservent getsockname getsockopt given glob gmtime goto grep groove gt h1 h2 h3 h4 h5 header hex hidden hr http https if image_button img import index insert int ioctl isindex join keys kill last lc lcfirst le length li link listen local localtime lock log lstat lt map maxsize minsize mkdir msgctl msgget msgrcv msgsnd multipart_end multipart_init multipart_start my ne next no not oct ol open opendir or ord our pack package param param_fetch password_field path_info pipe pop popup_menu pos pre print printf prototype push qq query_string quotemeta qw qx radio_group raise rand raw_cookie read readdir readline readlink readpipe recv redirect redo ref referer remote_addr remote_host remote_indent remote_user rename request_method require reset resizable return reverse rewinddir rindex rmdir say scalar script_name scrolling_list seek seekdir select self_url semctl semget semop send server_name server_port server_software set setgrent sethostent setnetent setpgrp setpriority setprotoent setpwent setservent setsockopt shift shmctl shmget shmread shmwrite shutdown sin sleep socket socketpair sort span splice split sprintf sqrt srand start_form start_h1 start_html start_multipart_form start_table start_ul startform stat state strict strong study sub submit substr symlink syscall sysopen sysread sysseek system syswrite table tagConfigure td tell telldir textarea textfield th tie tied time times title tmpFileName top tr truncate uc ucfirst ul umask undef unescape unescapeHTML unless unlink unpack unshift untie until update upload uploadInfo url url_param use use_named_parameters user_agent user_name utime values variable vec virtual_host wait waitpid wantarray warn when while width write x xor",
}

L.styles = {
	["PREPROCESSOR"] = {
		id = 9,
		fgColor = rgb(0xFFE0A0),
		bgColor = rgb(0xFFFFFF),
	},
	["DEFAULT"] = {
		id = 0,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
	},
	["INSTRUCTION WORD"] = {
		id = 5,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["NUMBER"] = {
		id = 4,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
	},
	["STRING"] = {
		id = 6,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["CHARACTER"] = {
		id = 7,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["OPERATOR"] = {
		id = 10,
		fgColor = rgb(0x569CD6),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["REGEX"] = {
		id = 17,
		fgColor = rgb(0x9CDCFE),
		bgColor = rgb(0x1E1E1E),
	},
	["COMMENT LINE"] = {
		id = 2,
		fgColor = rgb(0x6A9955),
		bgColor = rgb(0xFFFFFF),
	},
	["SCALAR"] = {
		id = 12,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
	},
	["ARRAY"] = {
		id = 13,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
	},
	["HASH"] = {
		id = 14,
		fgColor = rgb(0x9CDCFE),
		bgColor = rgb(0xFFFFFF),
	},
	["SYMBOL TABLE"] = {
		id = 15,
		fgColor = rgb(0xF44747),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 1,
	},
	["PUNCTUATION"] = {
		id = 8,
		fgColor = rgb(0xFFE0A0),
		bgColor = rgb(0xFFFFFF),
	},
	["POD"] = {
		id = 3,
		fgColor = rgb(0xD4D4D4),
		bgColor = rgb(0xFFFFFF),
	},
	["ERROR"] = {
		id = 1,
		fgColor = rgb(0xC586C0),
		bgColor = rgb(0xFFFFFF),
		fontStyle = 3,
	},
	["LONGQUOTE"] = {
		id = 19,
		fgColor = rgb(0xCE9178),
		bgColor = rgb(0xFFFFFF),
	},
	["DATASECTION"] = {
		id = 21,
		fgColor = rgb(0x858585),
		bgColor = rgb(0xFFFFFF),
	},
	["REGSUBST"] = {
		id = 18,
		fgColor = rgb(0x9CDCFE),
		bgColor = rgb(0x1E1E1E),
	},
	["BACKTICKS"] = {
		id = 20,
		fgColor = rgb(0xD7BA7D),
		bgColor = rgb(0x3C3C3C),
		fontStyle = 1,
	},
}
return L
