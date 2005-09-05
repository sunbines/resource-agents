/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2005 Red Hat, Inc.  All rights reserved.
 *
 * This copyrighted material is made available to anyone wishing to use,
 * modify, copy, or redistribute it subject to the terms and conditions
 * of the GNU General Public License v.2.
 */

#ifndef __UTIL_DOT_H__
#define __UTIL_DOT_H__

uint32_t gfs2_disk_hash(const char *data, int len);


#define fs_printk(level, fs, fmt, arg...) \
	printk(level "GFS2: fsid=%s: " fmt , (fs)->sd_fsname , ## arg)

#define fs_info(fs, fmt, arg...) \
	fs_printk(KERN_INFO , fs , fmt , ## arg)

#define fs_warn(fs, fmt, arg...) \
	fs_printk(KERN_WARNING , fs , fmt , ## arg)

#define fs_err(fs, fmt, arg...) \
	fs_printk(KERN_ERR, fs , fmt , ## arg)


void gfs2_assert_i(struct gfs2_sbd *sdp, char *assertion, const char *function,
		   char *file, unsigned int line) __attribute__ ((noreturn));

#define gfs2_assert(sdp, assertion) \
do { \
	if (unlikely(!(assertion))) { \
		gfs2_assert_i((sdp), #assertion, \
			      __FUNCTION__, __FILE__, __LINE__); \
	} \
} while (0)


int gfs2_assert_withdraw_i(struct gfs2_sbd *sdp, char *assertion,
			   const char *function, char *file, unsigned int line);

#define gfs2_assert_withdraw(sdp, assertion) \
((likely(assertion)) ? 0 : gfs2_assert_withdraw_i((sdp), #assertion, \
					__FUNCTION__, __FILE__, __LINE__))


int gfs2_assert_warn_i(struct gfs2_sbd *sdp, char *assertion,
		       const char *function, char *file, unsigned int line);

#define gfs2_assert_warn(sdp, assertion) \
((likely(assertion)) ? 0 : gfs2_assert_warn_i((sdp), #assertion, \
					__FUNCTION__, __FILE__, __LINE__))


int gfs2_consist_i(struct gfs2_sbd *sdp, int cluster_wide,
		   const char *function, char *file, unsigned int line);

#define gfs2_consist(sdp) \
gfs2_consist_i((sdp), 0, __FUNCTION__, __FILE__, __LINE__)


int gfs2_consist_inode_i(struct gfs2_inode *ip, int cluster_wide,
			 const char *function, char *file, unsigned int line);

#define gfs2_consist_inode(ip) \
gfs2_consist_inode_i((ip), 0, __FUNCTION__, __FILE__, __LINE__)


int gfs2_consist_rgrpd_i(struct gfs2_rgrpd *rgd, int cluster_wide,
			 const char *function, char *file, unsigned int line);

#define gfs2_consist_rgrpd(rgd) \
gfs2_consist_rgrpd_i((rgd), 0, __FUNCTION__, __FILE__, __LINE__)


int gfs2_meta_check_ii(struct gfs2_sbd *sdp, struct buffer_head *bh,
		       const char *type, const char *function,
		       char *file, unsigned int line);

static inline int gfs2_meta_check_i(struct gfs2_sbd *sdp,
				    struct buffer_head *bh,
				    const char *function,
				    char *file, unsigned int line)
{
	struct gfs2_meta_header *mh = (struct gfs2_meta_header *)bh->b_data;
	uint32_t magic = mh->mh_magic;
	uint64_t blkno = mh->mh_blkno;
	magic = le32_to_cpu(magic);
	blkno = le64_to_cpu(blkno);
	if (unlikely(magic != GFS2_MAGIC))
		return gfs2_meta_check_ii(sdp, bh, "magic number", function,
					  file, line);
	if (unlikely(blkno != bh->b_blocknr))
		return gfs2_meta_check_ii(sdp, bh, "block number", function,
					  file, line);
	return 0;
}

#define gfs2_meta_check(sdp, bh) \
gfs2_meta_check_i((sdp), (bh), __FUNCTION__, __FILE__, __LINE__)


int gfs2_metatype_check_ii(struct gfs2_sbd *sdp, struct buffer_head *bh,
			   uint16_t type, uint16_t t,
			   const char *function,
			   char *file, unsigned int line);

static inline int gfs2_metatype_check_i(struct gfs2_sbd *sdp,
					struct buffer_head *bh,
					uint16_t type,
					const char *function,
					char *file, unsigned int line)
{
	struct gfs2_meta_header *mh = (struct gfs2_meta_header *)bh->b_data;
	uint32_t magic = mh->mh_magic;
	uint16_t t = mh->mh_type;
	uint64_t blkno = mh->mh_blkno;
	magic = le32_to_cpu(magic);
	blkno = le64_to_cpu(blkno);
	if (unlikely(magic != GFS2_MAGIC))
		return gfs2_meta_check_ii(sdp, bh, "magic number", function,
					  file, line);
	if (unlikely(blkno != bh->b_blocknr))
		return gfs2_meta_check_ii(sdp, bh, "block number", function,
					  file, line);
	t = le16_to_cpu(t);
        if (unlikely(t != type))
		return gfs2_metatype_check_ii(sdp, bh, type, t, function,
					      file, line);
	return 0;
}

#define gfs2_metatype_check(sdp, bh, type) \
gfs2_metatype_check_i((sdp), (bh), (type), __FUNCTION__, __FILE__, __LINE__)

static inline void gfs2_metatype_set(struct buffer_head *bh, uint16_t type,
				     uint16_t format)
{
	struct gfs2_meta_header *mh;
	mh = (struct gfs2_meta_header *)bh->b_data;
	mh->mh_type = cpu_to_le16(type);
	mh->mh_format = cpu_to_le16(format);
}


int gfs2_io_error_i(struct gfs2_sbd *sdp, const char *function,
		    char *file, unsigned int line);

#define gfs2_io_error(sdp) \
gfs2_io_error_i((sdp), __FUNCTION__, __FILE__, __LINE__);


int gfs2_io_error_bh_i(struct gfs2_sbd *sdp, struct buffer_head *bh,
		       const char *function, char *file, unsigned int line);

#define gfs2_io_error_bh(sdp, bh) \
gfs2_io_error_bh_i((sdp), (bh), __FUNCTION__, __FILE__, __LINE__);


extern kmem_cache_t *gfs2_glock_cachep;
extern kmem_cache_t *gfs2_inode_cachep;
extern kmem_cache_t *gfs2_bufdata_cachep;

struct gfs2_user_buffer {
	char __user *ub_data;
	unsigned int ub_size;
	unsigned int ub_count;
};

int gfs2_add_bh_to_ub(struct gfs2_user_buffer *ub, struct buffer_head *bh);

static inline unsigned int gfs2_tune_get_i(struct gfs2_tune *gt,
					   unsigned int *p)
{
	unsigned int x;
	spin_lock(&gt->gt_spin);
	x = *p;
	spin_unlock(&gt->gt_spin);
	return x;
}

#define gfs2_tune_get(sdp, field) \
gfs2_tune_get_i(&(sdp)->sd_tune, &(sdp)->sd_tune.field)

int gfs2_printf_i(char *buf, unsigned int size, unsigned int *count,
		  char *fmt, ...) __attribute__ ((format(printf, 4, 5)));

#define gfs2_printf(fmt, args...) \
do { \
	if (gfs2_printf_i(buf, size, count, fmt, ##args)) \
		goto out; \
} while(0)

void gfs2_icbit_munge(struct gfs2_sbd *sdp, unsigned char **bitmap,
		      unsigned int bit, int new_value);

#endif /* __UTIL_DOT_H__ */

