//
// SaveMap.hpp for SAVE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sun May 22 20:58:47 2016 Victor Gouet
// Last update Sun May 22 21:04:21 2016 Victor Gouet
//

#ifndef SAVEMAP_HPP_
# define SAVEMAP_HPP_

# include <iostream>

class	SaveMap
{
public:
  SaveMap();
  ~SaveMap();

public:
  void		save();
  void		load(std::string const &);
};

#endif
