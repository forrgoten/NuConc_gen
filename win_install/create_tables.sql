CREATE TABLE isotopes (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(50) NOT NULL UNIQUE,
  mass INT NOT NULL,
  density DECIMAL(10,6) NOT NULL,
  abundance DECIMAL(10,8) NOT NULL,
  content DECIMAL(8,6) NOT NULL,
  fraction DECIMAL(8,6) NOT NULL
);

INSERT INTO isotopes (name, mass, density, abundance, content, fraction) VALUES 
('U235',235 ,19.1, 0.0072, 1, 0.004), 
('U238',238 ,18.9, 0.9928, 1, 0.003), 
('Pu239',239 ,19.8, 0.0000, 1, 0.005), 
('H1',1 ,0.0708, 0.99985, 1, 0.667), 
('H2',2 ,0.177, 0.00015, 1, 0.333);
