/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:51:41 by abarthel          #+#    #+#             */
/*   Updated: 2019/08/27 17:59:45 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERRNO_H
# define FT_ERRNO_H

extern const char	*const g_sys_errlist[];
extern const int	g_sys_nerr;
extern int			g_errno;

char				*ft_strerror(int errnum);
void				ft_perror(const char *s);

/*
** man 2 intro
*/

enum	e_errno
{
	E_EPERM = 1,
	E_ENOENT = 2,
	E_ESRCH = 3,
	E_EINTR = 4,
	E_EIO = 5,
	E_ENXIO = 6,
	E_E2BIG = 7,
	E_ENOEXEC = 8,
	E_EBADF = 9,
	E_ECHILD = 10,
	E_EDEADLK = 11,
	E_ENOMEM = 12,
	E_EACCES = 13,
	E_EFAULT = 14,
	E_ENOTBLK = 15,
	E_EBUSY = 16,
	E_EEXIST = 17,
	E_EXDEV = 18,
	E_ENODEV = 19,
	E_ENOTDIR = 20,
	E_EISDIR = 21,
	E_EINVAL = 22,
	E_ENFILE = 23,
	E_EMFILE = 24,
	E_ENOTTY = 25,
	E_ETXTBSY = 26,
	E_EFBIG = 27,
	E_ENOSPC = 28,
	E_ESPIPE = 29,
	E_EROFS = 30,
	E_EMLINK = 31,
	E_EPIPE = 32,
	E_EDOM = 33,
	E_ERANGE = 34,
	E_EAGAIN = 35,
	E_EINPROGRESS = 36,
	E_EALREADY = 37,
	E_ENOTSOCK = 38,
	E_EDESTADDRREQ = 39,
	E_EMSGSIZE = 40,
	E_EPROTOTYPE = 41,
	E_ENOPROTOOPT = 42,
	E_EPROTONOSUPPORT = 43,
	E_ESOCKTNOSUPPORT = 44,
	E_ENOTSUP = 45,
	E_EPFNOSUPPORT = 46,
	E_EAFNOSUPPORT = 47,
	E_EADDRINUSE = 48,
	E_EADDRNOTAVAIL = 49,
	E_ENETDOWN = 50,
	E_ENETUNREACH = 51,
	E_ENETRESET = 52,
	E_ECONNABORTED = 53,
	E_ECONNRESET = 54,
	E_ENOBUFS = 55,
	E_EISCONN = 56,
	E_ENOTCONN = 57,
	E_ESHUTDOWN = 58,
	E_ETOOMANYREFS = 59,
	E_ETIMEDOUT = 60,
	E_ECONNREFUSED = 61,
	E_ELOOP = 62,
	E_ENAMETOOLONG = 63,
	E_EHOSTDOWN = 64,
	E_EHOSTUNREACH = 65,
	E_ENOTEMPTY = 66,
	E_EPROCLIM = 67,
	E_EUSERS = 68,
	E_EDQUOT = 69,
	E_ESTALE = 70,
	E_EREMOTE = 71,
	E_EBADRPC = 72,
	E_ERPCMISMATCH = 73,
	E_EPROGUNAVAIL = 74,
	E_EPROGMISMATCH = 75,
	E_EPROCUNAVAIL = 76,
	E_ENOLCK = 77,
	E_ENOSYS = 78,
	E_EFTYPE = 79,
	E_EAUTH = 80,
	E_ENEEDAUTH = 81,
	E_EPWROFF = 82,
	E_EDEVERR = 83,
	E_EOVERFLOW = 84,
	E_EBADEXEC = 85,
	E_EBADARCH = 86,
	E_ESHLIBVERS = 87,
	E_EBADMACHO = 88,
	E_ELAST = 88,
	E_ECANCELED = 89,
	E_EIDRM = 90,
	E_ENOMSG = 91,
	E_EILSEQ = 92,
	E_ENOATTR = 93,
	E_EBADMSG = 94,
	E_EMULTIHOP = 95,
	E_ENODATA = 96,
	E_ENOLINK = 97,
	E_ENOSR = 98,
	E_ENOSTR = 99,
	E_EPROTO = 100,
	E_ETIME = 101,
	E_EOPNOTSUPP = 102
};

#endif
