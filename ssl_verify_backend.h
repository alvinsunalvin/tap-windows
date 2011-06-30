/*
 *  OpenVPN -- An application to securely tunnel IP networks
 *             over a single TCP/UDP port, with support for SSL/TLS-based
 *             session authentication and key exchange,
 *             packet encryption, packet authentication, and
 *             packet compression.
 *
 *  Copyright (C) 2002-2010 OpenVPN Technologies, Inc. <sales@openvpn.net>
 *  Copyright (C) 2010 Fox Crypto B.V. <openvpn@fox-it.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2
 *  as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program (see the file COPYING included with this
 *  distribution); if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * @file Control Channel Verification Module library-specific backend interface
 */

#ifndef SSL_VERIFY_BACKEND_H_
#define SSL_VERIFY_BACKEND_H_

/*
 * Backend support functions.
 *
 * The following functions are needed by the backend, but defined in the main
 * file.
 */

/*
 * Verify certificate for the given session. Performs OpenVPN-specific
 * verification.
 *
 * This function must be called for every certificate in the certificate
 * chain during the certificate verification stage of the handshake.
 *
 * @param session	TLS Session associated with this tunnel
 * @param cert		Certificate to process
 * @param cert_depth	Depth of the current certificate
 *
 * @return 		\c 1 if verification was successful, \c 0 on failure.
 */
int verify_cert(struct tls_session *session, x509_cert_t *cert, int cert_depth);

/*
 * Remember the given certificate hash, allowing the certificate chain to be
 * locked between sessions.
 *
 * Must be called for every certificate in the verification chain, whether it
 * is valid or not.
 *
 * @param session	TLS Session associated with this tunnel
 * @param cert_depth	Depth of the current certificate
 * @param sha1_hash	Hash of the current certificate
 */
void cert_hash_remember (struct tls_session *session, const int cert_depth,
    const unsigned char *sha1_hash);

/*
 * Library-specific functions.
 *
 * The following functions must be implemented on a library-specific basis.
 */

/*
 * Retrieve certificate's subject name, and place it in **subject.
 *
 * Memory for subject is allocated in the process, and must be freed.
 *
 * @param subject	Pointer to memory to be allocated for the subject
 * @param cert		Certificate to retrieve the subject from.
 *
 * @return 		\c 1 on failure, \c 0 on success
 */
bool verify_get_subject (char **subject, x509_cert_t *cert);

/*
 * Retrieve the certificate's username from the specified field.
 *
 * If the field is prepended with ext: and ENABLE_X509ALTUSERNAME is enabled,
 * it will be loaded from an X.509 extension
 *
 * @param cn			Buffer to return the common name in.
 * @param cn_len		Length of the cn buffer.
 * @param x509_username_field	Name of the field to load from
 * @param cert			Certificate to retrieve the common name from.
 *
 * @return 		\c 1 on failure, \c 0 on success
 */
bool verify_get_username (char *common_name, int cn_len,
    char * x509_username_field, X509 *peer_cert);

#endif /* SSL_VERIFY_BACKEND_H_ */