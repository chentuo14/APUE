#include <pwd.h>
#include <sys/types.h>

int main()
{
	struct passwd *user;
	while((user = getpwent()) != 0) {
		printf("%s:%d:%d:%s:%s:%s\n", user->pw_name, user->pw_uid,
				user->pw_gid, user->pw_gecos, user->pw_dir, user->pw_shell);
	}
	endpwent();
	return 0;
}
