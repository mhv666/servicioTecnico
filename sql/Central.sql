--
-- PostgreSQL database dump
--

-- Dumped from database version 10.6
-- Dumped by pg_dump version 10.6

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- Name: uuid-ossp; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS "uuid-ossp" WITH SCHEMA public;


--
-- Name: EXTENSION "uuid-ossp"; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION "uuid-ossp" IS 'generate universally unique identifiers (UUIDs)';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: cliente; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.cliente (
    id_cliente integer NOT NULL,
    nombre_cliente character varying NOT NULL,
    apellido_cliente character varying NOT NULL,
    tlf_cliente integer NOT NULL
);


ALTER TABLE public.cliente OWNER TO usuario;

--
-- Name: Cliente_id_cliente_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public."Cliente_id_cliente_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public."Cliente_id_cliente_seq" OWNER TO usuario;

--
-- Name: Cliente_id_cliente_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public."Cliente_id_cliente_seq" OWNED BY public.cliente.id_cliente;


--
-- Name: dispositivo; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.dispositivo (
    id_dispositivo integer NOT NULL,
    marca_dispositivo character varying(50) NOT NULL,
    modelo_dispositivo character varying(50) NOT NULL
);


ALTER TABLE public.dispositivo OWNER TO usuario;

--
-- Name: dispositivo_id_dispositivo_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.dispositivo_id_dispositivo_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.dispositivo_id_dispositivo_seq OWNER TO usuario;

--
-- Name: dispositivo_id_dispositivo_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.dispositivo_id_dispositivo_seq OWNED BY public.dispositivo.id_dispositivo;


--
-- Name: estado; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.estado (
    id_estado integer NOT NULL,
    nombre_estado character varying(50) NOT NULL
);


ALTER TABLE public.estado OWNER TO usuario;

--
-- Name: estado_id_estado_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.estado_id_estado_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.estado_id_estado_seq OWNER TO usuario;

--
-- Name: estado_id_estado_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.estado_id_estado_seq OWNED BY public.estado.id_estado;


--
-- Name: rma; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.rma (
    id_rma integer NOT NULL,
    id_cliente integer NOT NULL,
    id_estado integer NOT NULL,
    id_dispositivo integer NOT NULL,
    id_tecnico integer NOT NULL,
    id_tienda integer NOT NULL,
    descripcion_rma text NOT NULL
);


ALTER TABLE public.rma OWNER TO usuario;

--
-- Name: rma_id_rma_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.rma_id_rma_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.rma_id_rma_seq OWNER TO usuario;

--
-- Name: rma_id_rma_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.rma_id_rma_seq OWNED BY public.rma.id_rma;


--
-- Name: tecnico; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.tecnico (
    id_tecnico integer NOT NULL,
    nombre_tecnico character varying(50) NOT NULL,
    apellido_tecnico character varying(50) NOT NULL
);


ALTER TABLE public.tecnico OWNER TO usuario;

--
-- Name: tecnico_id_tecnico_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.tecnico_id_tecnico_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.tecnico_id_tecnico_seq OWNER TO usuario;

--
-- Name: tecnico_id_tecnico_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.tecnico_id_tecnico_seq OWNED BY public.tecnico.id_tecnico;


--
-- Name: tienda; Type: TABLE; Schema: public; Owner: usuario
--

CREATE TABLE public.tienda (
    id_tienda integer NOT NULL,
    nombre_tienda character varying(50) NOT NULL,
    tlf_tienda character varying(50) NOT NULL
);


ALTER TABLE public.tienda OWNER TO usuario;

--
-- Name: tienda_id_tienda_seq; Type: SEQUENCE; Schema: public; Owner: usuario
--

CREATE SEQUENCE public.tienda_id_tienda_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.tienda_id_tienda_seq OWNER TO usuario;

--
-- Name: tienda_id_tienda_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: usuario
--

ALTER SEQUENCE public.tienda_id_tienda_seq OWNED BY public.tienda.id_tienda;


--
-- Name: cliente id_cliente; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.cliente ALTER COLUMN id_cliente SET DEFAULT nextval('public."Cliente_id_cliente_seq"'::regclass);


--
-- Name: dispositivo id_dispositivo; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.dispositivo ALTER COLUMN id_dispositivo SET DEFAULT nextval('public.dispositivo_id_dispositivo_seq'::regclass);


--
-- Name: estado id_estado; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.estado ALTER COLUMN id_estado SET DEFAULT nextval('public.estado_id_estado_seq'::regclass);


--
-- Name: rma id_rma; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.rma ALTER COLUMN id_rma SET DEFAULT nextval('public.rma_id_rma_seq'::regclass);


--
-- Name: tecnico id_tecnico; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tecnico ALTER COLUMN id_tecnico SET DEFAULT nextval('public.tecnico_id_tecnico_seq'::regclass);


--
-- Name: tienda id_tienda; Type: DEFAULT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tienda ALTER COLUMN id_tienda SET DEFAULT nextval('public.tienda_id_tienda_seq'::regclass);


--
-- Data for Name: cliente; Type: TABLE DATA; Schema: public; Owner: usuario
--

INSERT INTO public.cliente VALUES (1, 'Juan', 'Ramon', 666555666);


--
-- Data for Name: dispositivo; Type: TABLE DATA; Schema: public; Owner: usuario
--

INSERT INTO public.dispositivo VALUES (1, 'Samsung', 's9');


--
-- Data for Name: estado; Type: TABLE DATA; Schema: public; Owner: usuario
--

INSERT INTO public.estado VALUES (1, 'Pendiente de validacion');
INSERT INTO public.estado VALUES (2, 'Preparado para la reparacion.');
INSERT INTO public.estado VALUES (3, 'Reparado.');
INSERT INTO public.estado VALUES (4, 'No reparado.');
INSERT INTO public.estado VALUES (5, 'Enviado a la tienda');


--
-- Data for Name: rma; Type: TABLE DATA; Schema: public; Owner: usuario
--

INSERT INTO public.rma VALUES (1, 1, 1, 1, 1, 1, 'movil roto');


--
-- Data for Name: tecnico; Type: TABLE DATA; Schema: public; Owner: usuario
--

INSERT INTO public.tecnico VALUES (1, 'Dormo', 'Nobisuke');


--
-- Data for Name: tienda; Type: TABLE DATA; Schema: public; Owner: usuario
--

INSERT INTO public.tienda VALUES (1, 'El corte', '555999888');


--
-- Name: Cliente_id_cliente_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public."Cliente_id_cliente_seq"', 1, true);


--
-- Name: dispositivo_id_dispositivo_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.dispositivo_id_dispositivo_seq', 1, true);


--
-- Name: estado_id_estado_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.estado_id_estado_seq', 5, true);


--
-- Name: rma_id_rma_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.rma_id_rma_seq', 1, true);


--
-- Name: tecnico_id_tecnico_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.tecnico_id_tecnico_seq', 1, true);


--
-- Name: tienda_id_tienda_seq; Type: SEQUENCE SET; Schema: public; Owner: usuario
--

SELECT pg_catalog.setval('public.tienda_id_tienda_seq', 1, true);


--
-- Name: cliente Cliente_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.cliente
    ADD CONSTRAINT "Cliente_pkey" PRIMARY KEY (id_cliente);


--
-- Name: dispositivo dispositivo_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.dispositivo
    ADD CONSTRAINT dispositivo_pkey PRIMARY KEY (id_dispositivo);


--
-- Name: estado estado_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.estado
    ADD CONSTRAINT estado_pkey PRIMARY KEY (id_estado);


--
-- Name: rma rma_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.rma
    ADD CONSTRAINT rma_pkey PRIMARY KEY (id_rma);


--
-- Name: tecnico tecnico_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tecnico
    ADD CONSTRAINT tecnico_pkey PRIMARY KEY (id_tecnico);


--
-- Name: tienda tienda_pkey; Type: CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.tienda
    ADD CONSTRAINT tienda_pkey PRIMARY KEY (id_tienda);


--
-- Name: rma rma_id_cliente_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.rma
    ADD CONSTRAINT rma_id_cliente_fkey FOREIGN KEY (id_cliente) REFERENCES public.cliente(id_cliente);


--
-- Name: rma rma_id_dispositivo_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.rma
    ADD CONSTRAINT rma_id_dispositivo_fkey FOREIGN KEY (id_dispositivo) REFERENCES public.dispositivo(id_dispositivo);


--
-- Name: rma rma_id_estado_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.rma
    ADD CONSTRAINT rma_id_estado_fkey FOREIGN KEY (id_estado) REFERENCES public.estado(id_estado);


--
-- Name: rma rma_id_tecnico_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.rma
    ADD CONSTRAINT rma_id_tecnico_fkey FOREIGN KEY (id_tecnico) REFERENCES public.tecnico(id_tecnico);


--
-- Name: rma rma_id_tienda_fkey; Type: FK CONSTRAINT; Schema: public; Owner: usuario
--

ALTER TABLE ONLY public.rma
    ADD CONSTRAINT rma_id_tienda_fkey FOREIGN KEY (id_tienda) REFERENCES public.tienda(id_tienda);


--
-- PostgreSQL database dump complete
--

