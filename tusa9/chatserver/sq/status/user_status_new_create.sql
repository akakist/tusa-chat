
DROP TABLE IF EXISTS `user_status_new`;
CREATE TABLE `user_status_new` (
  `ID` int(10) unsigned NOT NULL auto_increment,
  `uid` int(10) unsigned NOT NULL default '0',
  `name` text,
  `pic` int(11) default NULL,
  `disable_invite` char(1) NOT NULL default '0',
  `uniq` char(1) NOT NULL default '0',
  primary KEY (`ID`),
  KEY `uidi` (`uid`)
) ENGINE=MyISAM DEFAULT CHARSET=cp1251;

