<!DOCTYPE html><html>

<head>
    <meta charset="UTF-8" /><meta http-equiv="X-UA-Compatible" content="IE=edge" /><meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no" /><title>VŠB-TUO Login</title>
    <meta http-equiv="X-UA-Compatible" content="IE=edge"/><meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no"/>
        <link rel="stylesheet" type="text/css" href="/webjars/normalize.css/8.0.1/normalize.css" /><link rel="stylesheet" type="text/css" href="/webjars/bootstrap/5.1.3/css/bootstrap-grid.min.css" /><link rel="stylesheet" type="text/css" href="/webjars/material-components-web/13.0.0/dist/material-components-web.min.css" /><link rel="stylesheet" type="text/css" href="/webjars/mdi__font/6.2.95/css/materialdesignicons.min.css" /><link rel="stylesheet" type="text/css" href="/css/cas.css" /><link rel="stylesheet" type="text/css" href="/css/custom.css" /><link rel="stylesheet" type="text/css" href="/font/vsb-drive-font.css" /><link rel="shortcut icon"
        href="/favicon.ico" /></head>

<body class="login mdc-typography">
    <script type="text/javascript" src="/webjars/jquery/3.6.0/jquery.min.js"></script>
<script type="text/javascript" src="/webjars/es5-shim/4.5.9/es5-shim.min.js"></script>
    <script type="text/javascript" src="/webjars/css-vars-ponyfill/2.4.7/dist/css-vars-ponyfill.min.js"></script>
    <script type="text/javascript" src="/webjars/material-components-web/13.0.0/dist/material-components-web.min.js"></script>
<script type="text/javascript" src="/js/cas.js"></script>
<script type="text/javascript" src="/js/material.js"></script>
<script>
    if (typeof resourceLoadedSuccessfully === "function") {
        resourceLoadedSuccessfully();
    }
    $(function() {
        typeof cssVars === "function" && cssVars({onlyLegacy: true});
    })
</script>

<script>
    /*<![CDATA[*/

    var trackGeoLocation = false;

    var googleAnalyticsTrackingId = null;

    if (googleAnalyticsTrackingId != null && googleAnalyticsTrackingId != '') {
        (function (i, s, o, g, r, a, m) {
            i['GoogleAnalyticsObject'] = r;
            i[r] = i[r] || function () {
                (i[r].q = i[r].q || []).push(arguments)
            }, i[r].l = 1 * new Date();
            a = s.createElement(o),
                m = s.getElementsByTagName(o)[0];
            a.async = 1;
            a.src = g;
            m.parentNode.insertBefore(a, m)
        })(window, document, 'script', 'https://www.google-analytics.com/analytics.js', 'ga');

        ga('create', googleAnalyticsTrackingId, 'auto');
        ga('send', 'pageview');
    }

    /*]]>*/
</script>
<div>

    <header id="app-bar" class="mdc-top-app-bar mdc-top-app-bar--fixed mdc-elevation--z4 shadow-sm">
        <nav class="mdc-top-app-bar__row navbar navbar-dark bg-dark">
            <div class="container-fluid container-fluid d-flex align-items-center justify-content-between">
                <section class="mdc-top-app-bar__section mdc-top-app-bar__section--align-start">
                    </section>
                <section class="mdc-top-app-bar__section">
                    <span class="cas-brand mx-auto">
                        <span class="visually-hidden">VŠB-TUO</span>
                        <img id="cas-logo" class="cas-logo"
                            title="VŠB-TUO"
                            src="/images/vsb_en.svg"
                            /></span>
                </section>
                <section class="mdc-top-app-bar__section mdc-top-app-bar__section--align-end">
                    <!--                <a id="cas-user-account"--><!--                   th:href="@{/account}"--><!--                   th:if="${ticketGrantingTicketId != null}"--><!--                   class="mdc-icon-button mdc-top-app-bar__action-item"--><!--                   aria-label="User Account">--><!--                    <span class="mdi mdi-account-group"></span>--><!--                    <span class="visually-hidden">user account</span>--><!--                </a>--></section>
            </div>
        </nav>
    </header>
    <script>var countMessages = 0;</script>
    <script type="text/javascript">

        (function (material) {
            var header = {
                init: function () {
                    header.attachTopbar();
                    material.autoInit();
                },
                attachDrawer: function () {
                    var elm = document.getElementById('app-drawer');
                    if (elm != null) {
                        var drawer = material.drawer.MDCDrawer.attachTo(elm);
                        var closeDrawer = function (evt) {
                            drawer.open = false;
                        };
                        drawer.foundation.handleScrimClick = closeDrawer;
                        document.onkeydown = function (evt) {
                            evt = evt || window.event;
                            if (evt.keyCode == 27) {
                                closeDrawer();
                            }
                        };
                        header.drawer = drawer;
                        return drawer;
                    }
                    return undefined;
                },
                attachTopbar: function (drawer) {

                    var drawer = header.attachDrawer();
                    var dialog = header.attachNotificationDialog();

                    if (drawer != undefined) {
                        header.attachDrawerToggle(drawer);
                    }
                    if (dialog != undefined) {
                        header.attachNotificationToggle(dialog);
                    }
                },
                checkCaps: function (ev) {
                    var s = String.fromCharCode(ev.which);
                    if (s.toUpperCase() === s && s.toLowerCase() !== s && !ev.shiftKey) {
                        ev.target.parentElement.classList.add('caps-on');
                    } else {
                        ev.target.parentElement.classList.remove('caps-on');
                    }
                },
                attachDrawerToggle: function (drawer) {
                    let appBar = document.getElementById('app-bar');
                    if (appBar != null) {
                        let topAppBar = material.topAppBar.MDCTopAppBar.attachTo(appBar);
                        topAppBar.setScrollTarget(document.getElementById('main-content'));
                        topAppBar.listen('MDCTopAppBar:nav', function () {
                            drawer.open = !drawer.open;
                        });
                        return topAppBar;
                    }
                    return undefined;
                },
                attachNotificationDialog: function () {
                    var element = document.getElementById('cas-notification-dialog');
                    if (element != null) {
                        return material.dialog.MDCDialog.attachTo(element);
                    }
                    return undefined;
                },
                attachNotificationToggle: function (dialog) {
                    var btn = document.getElementById('cas-notifications-menu');
                    if (btn != null) {
                        btn.addEventListener('click', function () {
                            dialog.open();
                        });
                    }
                }
            }
            document.addEventListener('DOMContentLoaded', function () {
                if (material) {
                    header.init();
                }
                if (countMessages == 0) {
                    window.jQuery('#notifications-count').remove();
                } else {
                    window.jQuery('#notifications-count').text("(" + countMessages + ")")
                }
            });
        })(typeof mdc !== 'undefined' && mdc);
    </script>
</div>

    <div class="mdc-drawer-scrim"></div>

    <div class="mdc-drawer-app-content mdc-top-app-bar--fixed-adjust d-flex justify-content-center">
        <main role="main" id="main-content" class="container-lg py-4">
            <div id="content" class="d-flex justify-content-center">
   <div class="d-flex justify-content-center flex-md-row flex-column mdc-card mdc-card-content card flex-grow-1">
        <section id="loginForm"
                 class="login-section login-form card-body">
            <div class="d-flex flex-column justify-content-between m-auto">

        <div>
            <div id="serviceui" class="mb-4">
        <div class="d-flex align-items-center p-3">
            <img src="images/webapp.png"/><div id="servicedesc" class="ml-2">
                <h3>Kelvin</h3>
            </div>
        </div>
    </div>
        </div>

        <div class="form-wrapper">

            <form method="post" id="fm1" action="login">
                <div id="login-form-controls">
                    <h3 class="text-center">
                        <i class="mdi mdi-security fas fa-shield-alt"></i>
                        <span>Enter Username & Password</span>
                    </h3>

                    <section class="cas-field form-group my-3" id="usernameSection">
                        <label for="username"
                               class="mdc-text-field mdc-text-field--outlined control-label w-100">
                            <span class="mdc-notched-outline">
                                <span class="mdc-notched-outline__leading"></span>
                                <span class="mdc-notched-outline__notch">
                                    <span class="mdc-floating-label"><span class="accesskey">U</span>sername:</span>
                                </span>
                                <span class="mdc-notched-outline__trailing"></span>
                            </span>
                            <input class="mdc-text-field__input form-control" id="username"
                                   size="25"
                                   type="text"
                                   accesskey="u"
                                   autocapitalize="none"
                                   spellcheck="false"
                                   autocomplete="username" required name="username" value=""/></label>

                        <div class="mdc-text-field-helper-line">
                            <div class="mdc-text-field-helper-text mdc-text-field-helper-text--validation-msg" aria-hidden="true">
                                <span id="usernameValidationMessage">Username is a required field.</span>
                            </div>
                        </div>

                        <script type="text/javascript">
                            /*<![CDATA[*/
                            var username = "";
                            var disabled = false;

                            if (username != null && username !== '') {
                                $('#username').val(username);
                                if (disabled) {
                                    $('#usernameSection').hide();
                                }
                            }
                            /*]]>*/
                        </script>
                    </section>
                    <section class="cas-field form-group my-3 mdc-input-group form-group" id="passwordSection">
                        <div class="mdc-input-group-field mdc-input-group-field-append">
                            <div class="caps-check">
                                <label for="password"
                                       class="mdc-text-field caps-check mdc-text-field--outlined control-label mdc-text-field--with-trailing-icon control-label w-100">
                                    <span class="mdc-notched-outline">
                                        <span class="mdc-notched-outline__leading"></span>
                                        <span class="mdc-notched-outline__notch">
                                            <span class="mdc-floating-label"><span class="accesskey">P</span>assword:</span>
                                        </span>
                                        <span class="mdc-notched-outline__trailing"></span>
                                    </span>
                                    <input class="mdc-text-field__input form-control pwd"
                                           type="password"
                                           id="password"
                                           size="25"
                                           required
                                           accesskey="p"
                                           autocomplete="off" name="password" value=""/></label>
                                <div class="mdc-text-field-helper-line">
                                    <div
                                            class="mdc-text-field-helper-text mdc-text-field-helper-text--validation-msg"
                                            aria-hidden="true">
                                        <span id="passwordValidationMessage">Password is a required field.</span>
                                    </div>
                                </div>
                                <div class="mdc-text-field-helper-line caps-warn">
                                    <div
                                            class="mdc-text-field-helper-text mdc-text-field-helper-text--persistent mdc-text-field-helper-text--validation-msg text-danger">
                                        <span>CAPSLOCK key is turned on!</span>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </section>

                    <section class="cas-field form-group my-3">
                        </section>


                    <section class="cas-field">

                        <input type="hidden" name="execution" value="fbc10f4f-7eb9-451d-b06f-8bf0e0fc8ae9_ZXlKaGJHY2lPaUpJVXpVeE1pSXNJblI1Y0NJNklrcFhWQ0o5LmRKTGc5eTlSVjBvcnFBTFByWFFTSjZuNF9JNkExUUNuckNvX2FLamdvOERBbWdmdVduZTlSTzRCTlhRQ3loWi1vVVMwcHpQX1RXcVM5N2FDOXJoS2h5ZjFWeHllZ3d5MWgybnBkblRfc1puYVhRY2RxOGY1TnBFOFFia0hRb1p3RVllRnZqWW9qTkhjVkMwVWUzeXNySWhhNkwwaUYtUDZ0V1FlMWVYZGlFM0xETlVCLVhDQ1lrZERwdVBONFg5T1NVNGJRUmZZbkNnaFY4TGY3Vk1abmpveG15OEk1SlRJMkstYWhuNlRzYV9jRC1GRHlCak53S2JRYTAtMzRWMV9tejV1OFEyZ0tvRjdVY0daNmhSUTBLcGtSaFB3dVNVRjdBa0M2NUhGcUxfajJOLW1jU3VxYTJzZmU3M1YxSXB1eGozemFHWEp3T1V2WW9iWWVhN3lINDBpYXlBaDYzeEx4YzRGdV9NLWlWUi1sQWNtX202RU9lbVFnVjRHZ1pJZk5nRjJBYlFBRlFKNEpJRUNybmlVeVF1bDN0MWhVX0pvdjBxemViMXNtTlpjSnJJRTdkWGNsTnRUNElZWl9tckFfVnVYQWdYeDROTHk0amlfTnRsVTVJWjU0bnZyLURlaEZFeE5VbHUyaEwxOGVoRjlHd1puMFlYRXVOUHNMaXY3UW5uM3gxd2txeks2MFRHeEFSVXYtRVJOeUtUSHYyQklKa2o3QXlSNGtneXVIcDZtNXRMTlJIY252ZjdNQTl3VUwyOGQ2WFUyYmZzdHJhS1ZrbTFWSGpoLWFMalFneUZ5eWFFQ3BGazFUOGtyS19XVGVUVzM5ZngwQkJKSjlIRzdnNHJOckV5TWd2Tm1TRk85OUJpa1BXZlBrdF9aSjZzckpMeVE0andDZHhDcFpzbWVOM3JYeDFxbXNJYWg2WkNtbEM1SGkzSVJIU3RCSkV6RERQZHRrNVBHQTVQdFVoSlNKVENiY1FuTFRySVI4UmRYX3lWSVU5eHp1dEoxZXFZbHU5cFMzWDR5TGtWWkU4c2N0UXgwTXhmUzFrcl9IRlRjYjdaYnBNRHQydVMwbFZpY3p3TF9LbjJ0blg2cEZKRmRiUmRvMjRGTnZRY3lNSDA3ZlJLdV9rR2dSZnhSeVpYR21oM2Z1emVYRW9XaE1XamI5aS1UNHJkUnJFVFotemlKWjJYMXQ3VDVLVmpOVnJReEM0VU1YMFpuUUxRTVQycEFJQUJ1Z18zR3NKMG51Szc5cjI2bEJlYm1YSG14SG15a1A4aE9vOTN5MmVoUV9tbGhGZ2VsVmJXeFR4WG0tdXRJcTJMQkpNUG5BNzBieEIweDNwcmtxTGtiVGphUDdHRVlrOWNLbzRMVXdpMjBmektTNnRxV2thdFBXN0VWa0RqakN6bVZPd2Z6LWZhX0dMaVdpVm9XVUViOGxHQVdqYkxwMDEydG16enI3X1VIbDJJQmV6TXM1RjNLaGdGandrLVV2cVBRdUlULW9qQjlOV1dpRkhsZGUwZWJtSGJ4SUJoRmQ4QUVKbk41bDM1NlhVRVlNdDE3M2hmN0xKSW1hQ2RtN1FLVFdVQzVwdnozak8xRDhORGNVLXp4Nm1vRWljcklvOC1sQWs2Mk01TEw4SDRHWVowNzZFbzVpUElOQVJzRlB3UUNzUGtEQWw4bldxZl9pY05tS3JGNlZGUmNtbWN3a21XUUJBa2lta1FIVTQ5UnROSExkdmduMjY5V0FOcHozclZsMjY4OVJfemJNb2dqOVd1RnFXYnBoMFNnVTF5a1JiTldkeUh6VHViZHV3elBCQzhBajQtMjQ0YTI4eGtlZURUcTE4UFpfWVp3aXBiRWZuSUlLa19GU0xXZE5yekJFQy10UVVEOFVjd2tkeGVDck1pdEJCWUN5Y3U3eDdWUXZuRXdNRFhuVm5JYlM0bHlKWlZZdFVwdnZ5cnp1OWxtSDFiaVVXYmU1RFlqSXR0UnBnb2UwNEtpcjEwNzAzRjVrMWF6U3ZjMzNfXzU5cEIzNzI2T2NvQ1pmVjlJdmVId2ltMDdkM1YxZl9DR25nclYtLWdZRHdVUm10RGpWdkhFLTZnRnlMZnVadEprVHZhcEZhZElveEVZbmJYYWh5QjNweWtlSE95b1BfdDZ0Tk0wMGxrSTdlNlAya25jM3pkQ0JLVTZWMC1ZRzNnMHFGeEo0MzBCb29VX1dTa0cwbWpCdWZsOFQ2U0RoLUNpeHB6U0F5VzdTc0FHVUljTmxSNHM4WnRKYmhxQ1F2QzI2dTFIX01HUmU2ZWV0cHVPN1lXclRjM2pqWGZmZ0tmdkV0RzFqNGZxVTZvd01GNFJmcExmZjNENm1EN2VTS1JnUjVsM2FSUVZMTWJ6eTVvNXNCbmZzWjN3TzdRX0dWSUVDV3ZtV05qV0x0Y2FNN0NGbkJfREJuX2cwaElfdUJ0UGU5bENGNFB2amJNdlY2cEsxTndTVlhjR3d6NUVaT3Nza1pZbnJwLUlWS1VOcDBJX1FNbVh4Ylh2U0syTUxXQWxPVUk0alh2emNSZU1kXzIwNU0zSmNOOXZBLUtRN1c3eUo4b283akdqSVJsWVRVaW0xQlJzWDFQZGFCdzVjTkN0RF9SdU9Zd2owVGJiUmlLMVhocnAwV0lBYnVOYmVxU2hoVzlDZXQweUI2UUFXdW5Fdm5ycG9GMW1ZZXZKVVV5bm9CV0MxMkpJRUFoaVRPV1p3THE5cGFMUlZkb3Btcl85ckh5YkhmTjF4ZXdSSTE1WEh6aFNzZklGLXZodEVpdTNEUmN4dHNqYnM1dlNYYkhVZExxamRyb2FKczFjM0ozdDBSS3FsYlNMUU4teG0wcllFeHJyMkYzWWMwakdZcWI0ZUtMZTJ4SllkeHhHZVJ5cUtWOG9QMG1hYW9Bc1Z5SGd0OHVCZlFEUURoZGtyV0hfNVp3THhVV1lVREx3bGZ1eWFadXNocFZsZnZEejhTdklVQVNCSlFDT2Q3eDlfY2t3ZWtrMVh1YXFXN0JyN3J4UG1KREZyZFk5UFh5ZUZ3aWFKSjhncFg2ZlhJeFU3S1RGVmVnS0ZLMmlIdjJIY0pNcWFUeDlYQ3BpLVZ3NlQwTUI2MGp4MXBiaU45cnQ2TE84THlHcHRfTTZNMzNOd2NRVXI3MnZ1akV3TmppWHdMY2RzNmt6VnJ4blB0d1QybU9IdUlFTUNndER5R1dwekk4eDV3QzFQZmFfeDFWTER5U0dCYW5jQlJvdjMzbU5VRHFnOW52OFFkTVdEU0RJUG1PR3RfODFZeXZvM1lKZklaRDhOWm5NRXB6Z3JBUk5wR0JTc3FTWUxXeVRtT1Q5ZF9NZ1BKaUU2VDhnODNWTjVrZGVCUHJVMTltTVdpbUxOTXpKT2pWR1YyYlJLVDQzUFhQQnA0cWtUZ0ZWR0wyUE9YNXhWbU1RYm9ndEdHcElpUmsyRkpBaUdqZGdLWGpxSlJ4NlZFaUk4M0Z3Y2lKTS1mMzhvRmpWMkM3eVpCOWcybi1fN09fSGx4N1ZHV1BKYmVMZWdYaXRyX2pTTnItb1JNTXYzdUVSYUU2TV9OUmV5US1vY3lPbXM0cjBob3JtdjBicHo4MHN4ZnhYQmU4MExTb2g0NExOMVE4Q2VDYmtIOU1jU2MtejIzdzhGREpZRThMYVZyWExjYXZEX2dqVTlOZDlEOTlKVnZnTThvQjFIaTdkNG5UZFdSWVJjbmpUUERMM0d6aEJ6clRlaGJHYVdfanBlcmtHSkoxSXB0RjR6eTlsRnlZb3FxTnF6OTdQTFNsTzlMcHo1b3JuYlVzT1RBSlpOenp6akMxTFVYU01fSUxEbENic2RHT0ZOV0F6aDZuLWVWTmFlSE1UTE9ZOG5rb0dHYzhRUEFMUlVFcVV4bmo0LThCX2xUQ2t6RlVRSTE0OVFmVVN5bG1LLXFza1ZHOGlBMU1ubFFnU1pTYlFXd0MtUUVBMElrR2pBLVpzeUVaWFVYSkdpc2tDS1RwOF9MV1V5M0s3NzFsbWthSXJxeklWMHpSRkQ5MEZkYlBMY1QtcU5ST3IzVkwyZ1ZkRGNCWGE4amJZWVFuR1lfREdpalVHZkh5a2VpOFd3VERaeWVheU02SkI5bnk0Skh1Qk56cEw0Z0hUY3lJQmwwdTdVOTBBRE9fSWFQRHNqSUFReFhENENieDNDaEtxLW4xQWZfYy1yOElKNjRPaWdwTkJYYzVtbzZvdEdiNGZNV2tCRU12WTUzOVhfTlU4TkhZanRDZ1NDbURzRDd4MjAweWxfTXBBRExNckVWQ0VzTWpKM2VfY3lkbDUxcjRKR3FQQmpTUUVHMFZmRkt4T3NkWkFJYmpsZGJZLXBiSFhXOUo0ZHlRam5iU3VpT3U2STZ6TDR5eFFjYXhmRDdiNkJ2OF9FUUpGMHp6Nkg4c2gzamxZUUhSb0NIcWwzOE96MnBGMnFNWUN2eFZGNjdYd244RU52eEFpcno3bGxYWWxCZ1RaZVhnaGdhWkF4YlhVNVpmcnNJb0NiU3Z4WjYzVGtESTVpcVFZOEJCa0FoMXR6REF2S2RfbEFQS2R3V3k5ZVZFUkR6Sm9tVGw4bHRLMThpU3B5enE1eTZRWjBfRmFmUld1bTBNaVRfcWhfVXhIU3ZWVm5zLXNLSWpHUEE5RTJERkFhTkZqVlRyZjlGZnJ1em4yd3BwUVlzWmd2Qnp4ZXRNc1lCd3pxcjN6QnBhWXVINkdfbTNIZVB5RERhU0VRZkJCWkxJejl5VTJELTROaEl6aWktellNVWNqdjVqX2hkLUxfMXJHdUlkbXlybUlfZXVoZlRUTkNIN0hEMHM3SkdFYldROWZlZVRNSjRJVXRpQXpUY0ZWUzdabl8zVFdpX2xXX1hUVXluR2x0TTJUMEx2enA0WjJBRDhDMEsyNjNib1hHRm85RGs0bE9BeVVXZkNiZkN6dlc1MWc3cGNJVm9OMlFJdE5rVTBkZjZZNUlLSUt5eDd2UzNkQjZldTRNU2NlT3EzaW16YzE2V2J2TjY2LU1jRTBMTGhNQUhjUE53X2s5SUlBdU92V0FweEhGMnh5ZGhpNUtzaDZOYU9aNUJFbWd4Nk5hTjhXcmZYSG5tZEpkQnNDbzB2Z2ZrRGRCV0NlLWVpaWxtejFXUTYycUpuMG95NGtmSUZ0YlI1Smwyd0ktV1FJcUpQNll2Nk9scWN2eHhvTWVZekRtVG8xbGtLdVhULWktNnIzUmh2VTYzWGwtVlNTVmJiZ181b3JCcE1tR2RJbFhqRnpZTndRb2VtQnhQVmFHcmRDSXI1RTFXNlM0bEpMWmRtQW1US1hoS1JFSEItY3g0N1BvUG9QOHJKZW81MHU5N0J2YVRUV3dYTEJjLUxreVhlbnJiWE15bnROcnk2UU9xc1dIdk5FV1RHa2ctcGFaOUVSa1pjSjZob3hZVWgycmZ5SlJlSXg0MUt4Smt0VEU1cWg3US4wTUZISTNjYnI0SFJUUVhNUUFWbmdlNkZVT0Vzd2ZjaHhVTjN5NVFETEs1MHUtZzk1ZThyQTZSdFBPaDVGTmZaQkVfSkZYZ0l6ZHZyUEpVSmxCQzRWZw=="/><input type="hidden" name="_eventId" value="submit"/><input type="hidden" name="geolocation"/></section>

                    <button
                class="mdc-button mdc-button--raised btn btn-primary btn-primary"
                name="submit"
                accesskey="l"
                type="submit">
            <span class="mdc-button__label">Login</span>
        </button>

        </div>
            </form>

            <hr class="my-4"/><span>
                    <div id="pmlinks" class="my-2">
        <div>
<!--             <br />  
            <span class="mdi mdi-account-question"></span> --><span><a href="https://idoc.vsb.cz/xwiki/bin/view/uzivatel/hesla/jednotne-heslo">Forgot your password? </a></span>
        </div>
    </div>
                </span>

            <script type="text/javascript">
                /*<![CDATA[*/
                var i = "One moment please..."
                var j = "Login"
                    /*]]>*/
                    $(window).on('pageshow', function () {
                        $(':submit').prop('disabled', false);
                        $(':submit').attr('value', j);
                    });
                $(document).ready(function () {
                    $("#fm1").submit(function () {
                        $(":submit").attr("disabled", true);
                        $(":submit").attr("value", i);
                        return true;
                    });
                });
            </script>
        </div>

        <span>
            <div id="sidebar">
            <div class="sidebar-content">
                <p>For security reasons, please <a href="logout">log out</a> and exit your web browser when you are done accessing services that require authentication!</p>
            </div>
        </div>
        </span>

    </div>
        </section>
        <span>
            </span>
        </div>
    <div class="login-side-info">

        <div id="serviceui" class="mb-4">
        <div class="d-flex align-items-center p-3">
            <img src="images/webapp.png"/><div id="servicedesc" class="ml-2">
                <h3>Kelvin</h3>
            </div>
        </div>
    </div>

        <section id="loginInfo"
                 class="login-info">
                 <p>You are logging into <strong>Single Sign On system (SSO)</strong>. After a single login, this system enables you to access multiple secured applications (e.g. portal, EPS) using an unique web browser instance.</p>
                 <p>As for Username and Password, please use the <strong>username</strong> and <strong>password</strong> from <strong>LDAP</strong> (ie. username and password used for logging reading the mail).</p>
        </section>
    </div>
</div>
        </main>
    </div>

    <footer class="py-4 d-flex justify-content-center align-items-center cas-footer">
    <span>&copy; 2004 - <span>2024</span> <span title="6.5.4 5/20/22, 4:46 AM">CIT</span>, VŠB-TUO</span>
</footer>

</body>

</html>
