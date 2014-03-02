Description
===========
This drupal module allows site admins to create simple, ajaxy email list signup forms for organizations that use the Convio Luminate Online CRM.

The signup forms created by this module create constituent records in the Convio Luminate Online database via Convio's createOrUpdate API method (http://open.convio.com/api/#constituent_api.createOrUpdate_method.html). To use this module, the Convio API module, which sends and processes Convio API requests, must first be installed and configured.


Usage
=====
Once the convio_api and convio_signup modules are installed and configured, an admin can create new signup blocks by visiting Administration > Structure > Convio Signup Forms Configuration > Create Convio Signup Form. After filling out and submitting the form on this page, a new block containing the email signup form is available for admins to place on the site (Administration > Structure > Blocks).

To edit or delete existing blocks, admins can visit Administration > Structure > Convio Signup Forms Configuration page. Easy access to the Convio API configuration and Convio Signup Form creation pages are also available on this page.


Dependencies
============
* Convio API module - https://github.com/milodesc/convio_api
* Convio service and API credentials


Resources
=========
convio_api module: https://github.com/milodesc/convio_api
Convio API createOrUpdate documentation: http://open.convio.com/api/#constituent_api.createOrUpdate_method.html
Convio API general documentation: http://open.convio.com/api/#main


Credits
=======
Though not a direct fork, this project initially leaned heavily on jtolj's convio_signup module (https://github.com/jtolj/convio_signup).
