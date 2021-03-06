#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <algorithm>
#include <cstring>
#include <glib.h>
#include <map>
#include <string>
#include <vector>

#include "compiler.hpp"

struct less_str {
  bool operator()(const char *lh, const char *rh) const {
    return strcmp(lh, rh)<0;
  }
};
typedef std::map<const char*, const char *, less_str> Str2StrTable;

class ReplaceStrTable {
public:
	typedef std::vector<std::pair<const char *, const char *> >::iterator iterator;
	typedef std::vector<std::pair<const char *, const char *> >::const_iterator const_iterator;
	const char *&operator[](const char *str) {
		for (iterator it = tbl_.begin(); it != tbl_.end(); ++it)
			if (strcmp(it->first, str) == 0)
				return it->second;
		tbl_.push_back(std::make_pair(str, ""));
		return tbl_.back().second;
	}
	const_iterator begin(void) const { return tbl_.begin(); }
	const_iterator end(void) const { return tbl_.end(); }
	bool empty(void) const { return tbl_.empty(); }

private:
	std::vector<std::pair<const char *, const char *> > tbl_;
};

extern void replace(const ReplaceStrTable& replace_table,
		    const char *str, std::string& res);

extern bool make_directory(const std::string& dir);

static inline void tolower_ascii(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), g_ascii_tolower);
}

static inline void toupper_ascii(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), g_ascii_toupper);
}

static inline bool is_file_exist(const std::string& file)
{
	//To fix compiler warning
	if (g_file_test(file.c_str(), G_FILE_TEST_EXISTS))
		return true;
	return false;
}
typedef std::vector<std::string> StringList;
extern StringList split(const std::string& str, char sep);
extern void strip(std::string& str);
extern const char *b64_encode(guint32 val, char result[7]);
extern guint32 b64_decode(const char *val);

extern bool copy_file(const std::string& from, const std::string& to)
	ATTRIBUTE_WARN_UNUSED_RESULT;
extern size_t truncate_utf8_string(const char* const beg, const size_t str_len, const size_t max_len);

#endif//!_UTILS_HPP_
