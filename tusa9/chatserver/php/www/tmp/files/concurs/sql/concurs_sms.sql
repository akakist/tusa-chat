
DROP TABLE IF EXISTS `concurs_sms`;
CREATE TABLE `concurs_sms` (
  `ucha` int(20) unsigned NOT NULL default 0,
  dt datetime not null default '2008-01-01'
) ENGINE=MyISAM  DEFAULT CHARSET=cp1251;


DROP TABLE IF EXISTS `concurs_ucha`;
CREATE TABLE `concurs_ucha` (
	ucha int(20) unsigned NOT NULL default 0,
	nick text,
	uid int(20) unsigned NOT NULL default 0,
	primary key (ucha)
) ENGINE=MyISAM  DEFAULT CHARSET=cp1251;


DROP TABLE IF EXISTS `concurs_vote`;
CREATE TABLE `concurs_vote` (
	who int(20) unsigned NOT NULL default 0,
	ucha int (20) unsigned NOT NULL default 0,
	primary key(who)
) ENGINE=MyISAM  DEFAULT CHARSET=cp1251;

set CHARSET cp1251;


insert into concurs_ucha values ('1','Anu_tka','308288');
insert into concurs_ucha values ('8','Stasy','107583');
insert into concurs_ucha values ('9','Гёрла','152545');
insert into concurs_ucha values ('10','Резвик','250202');
insert into concurs_ucha values ('23','COOL_ДеVаХа','265027');
insert into concurs_ucha values ('27','Чернушечка','227883');
insert into concurs_ucha values ('29','Cens','47178');
insert into concurs_ucha values ('32','Ки$Ка_БяКа','272937');
insert into concurs_ucha values ('45','Jl_юбимая','313268');
insert into concurs_ucha values ('48','Бусunka','345495');
insert into concurs_ucha values ('50','Дашулька_вишенка','313420');
insert into concurs_ucha values ('72','Sadistk_OY','243391');
insert into concurs_ucha values ('78','Paradi$e','63359');
insert into concurs_ucha values ('80','Высоковольтная','71581');
insert into concurs_ucha values ('84','стерваSex','318274');
insert into concurs_ucha values ('86','Твоя_проблема','213843');
