DROP TABLE IF EXISTS mcassa_requests;                             
CREATE TABLE mcassa_requests (                                    
  ID int(10) unsigned NOT NULL auto_increment,           
  user varchar(50) NOT NULL default '',                 
    head_dt datetime  NOT NULL default '2005-01-01 00:00:00',                     
    dt datetime  NOT NULL default '2005-01-01 00:00:00',                     
    op_id  int(11) NOT NULL default '0',    
    op_point int(11) NOT NULL default '0',    
    op_service  int(11) NOT NULL default '0',    
    op_dt datetime  NOT NULL default '2005-01-01 00:00:00',                     
    op_total double NOT NULL default '0', 
    op_account varchar(50) NOT NULL default '',
  PRIMARY KEY  (ID),                                     
  KEY op_dt (op_dt),                                            
  KEY dt (dt)                                            
) TYPE=MyISAM;                                           
                                                         