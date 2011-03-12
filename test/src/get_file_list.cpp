/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "get_file_list.hpp"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

std::vector<std::string>
get_file_list(const std::string& path_str, const boost::regex& regex, const bool recursive)
{
	namespace fs = boost::filesystem;

	std::vector<std::string> filenames;

	fs::path full_path(path_str);

	fs::directory_iterator end_iter;
	for
	(
		fs::directory_iterator dir_itr(full_path);
		dir_itr != end_iter;
		++dir_itr
	)
	{
		if(fs::is_directory(dir_itr->status()) && recursive) //if the item is a directory...
		{
			//recursively get its files...
			std::vector<std::string> subdir_filenames = get_file_list(dir_itr->path().string(), regex);

			//... and append them to the list
			std::insert_iterator<std::vector<std::string>> filenames_ii(filenames, filenames.end());
			std::copy
			(
				subdir_filenames.begin(),
				subdir_filenames.end(),
				filenames_ii
			);
		}
		else if(fs::is_regular_file(dir_itr->status())) //if the item is a file...
		{
			if(boost::regex_match(dir_itr->path().string(), regex)) //if the file's name matches the regex...
			{
				//append it to the list
				filenames.push_back(dir_itr->path().string());
			}
		}
	}

	return filenames;
}

